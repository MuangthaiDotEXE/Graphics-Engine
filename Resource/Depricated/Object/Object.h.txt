#pragma once

#ifndef OBJECT_H
#define OBJECT_H

#include <glad/gl.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"
#include "Texture.h"

namespace Engine
{
	class Object
	{
	public:
		Core::Shader shader;

	private:
		Core::VAO vao;
		Core::VBO vbo;
		Core::EBO ebo;
		Core::Texture texture;
		Core::Texture specularMap;
		GLuint* textures;
		GLuint* specularMaps;

	public:
		Object();
		virtual ~Object();

		void Render();
		void Update();
	};
}

#endif
