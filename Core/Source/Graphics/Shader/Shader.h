#pragma once

#ifndef SHADER_H
#define SHADER_H

#include <sstream>
#include <fstream>
#include <iostream>
#include <type_traits>
#include <concepts>
#include <string>
#include <print>
#include <stdexcept>

#include <glad/gl.h>

#include "Utility/Utility.h"

namespace Core
{
	class Shader
	{
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
