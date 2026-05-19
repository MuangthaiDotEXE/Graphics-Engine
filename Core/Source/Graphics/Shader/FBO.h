#pragma once

#ifndef FBO_H
#define FBO_H

#include <stdexcept>

#include <glad/gl.h>
#include <glm/glm.hpp>

namespace Core
{
	class FBO
	{
	private:
		GLuint fboID, colorTexture, rboID;
		int width, height;

	public:
		FBO(glm::vec2 size);
		virtual ~FBO();

		void Bind();
		void Unbind();
		void Resize(glm::vec2 size);

		GLuint GetColorTexture() const;
		glm::vec2 GetSize() const;

	private:
		void Create();
		void Destroy();
	};
}

#endif
