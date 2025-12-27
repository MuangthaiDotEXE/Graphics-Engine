#ifndef SHADER_H
#define SHADER_H

#include <sstream>
#include <fstream>
#include <iostream>
#include <string>
#include <print>
#include <stdexcept>

#include <glad/gl.h>

namespace Engine
{
	class Shader
	{
	private:
		std::string ReadFile(const std::string& path);

	public:
		GLuint programID;

		Shader(const std::string& vertexPath, const std::string& fragmentPath);
		virtual ~Shader();

		void Activate();
		void Delete();

	private:
		void Error(GLuint shader, const std::string& type);
	};
}

#endif
