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

template<typename T>
concept string = std::is_same_v<T, std::string> || std::is_convertible_v<T, char*>;

namespace App
{
	class Shader
	{
	private:
		template<string T>
		std::string ReadFile(const T& path);

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
