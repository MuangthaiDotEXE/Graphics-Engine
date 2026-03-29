#include "FBO.h"

Core::FBO::FBO(int width, int height)
	: width(width), height(height)
{
	Create();
}

Core::FBO::~FBO()
{
	Destroy();
}

void Core::FBO::Bind()
{
	glBindFramebuffer(GL_FRAMEBUFFER, fboID);
	glViewport(0, 0, width, height);
}

void Core::FBO::Unbind()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Core::FBO::Resize(int width, int height)
{
	if (width == this->width && height == this->height) return;

	this->width = width;
	this->height = height;

	Destroy();
	Create();
}

GLuint Core::FBO::GetColorTexture() const
{
	return this->colorTexture;
}

glm::vec2 Core::FBO::GetSize() const
{
	return glm::vec2(this->width, this->height);
}

void Core::FBO::Create()
{
	glGenBuffers(1, &fboID);
	glBindFramebuffer(GL_FRAMEBUFFER, fboID);

	glGenTextures(1, &colorTexture);
	glBindTexture(GL_TEXTURE_2D, colorTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, colorTexture, 0);

	glGenRenderbuffers(1, &rboID);
	glBindRenderbuffer(GL_RENDERBUFFER, rboID);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rboID);

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
	{
		throw std::exception("Framebuffer is not created completely (OpenGL graphics API)\n");
	}

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Core::FBO::Destroy()
{
	glDeleteFramebuffers(1, &fboID);
	glDeleteTextures(1, &colorTexture);
	glDeleteRenderbuffers(1, &rboID);
}
