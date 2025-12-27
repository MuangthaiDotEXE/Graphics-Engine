#ifndef MESH_H
#define MESH_H

#include <glad/gl.h>

#include "Shader.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"

namespace Engine
{
	class Mesh
	{
	private:
		Shader shader;
		VAO vao;
		VBO vbo;
		EBO ebo;

	public:
		Mesh();
		virtual ~Mesh();

		void Render();
		void Update();
	};
}

#endif
