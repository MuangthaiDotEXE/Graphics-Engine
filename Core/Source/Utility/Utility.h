#pragma once

#ifndef UTILITY_H
#define UTILITY_H

#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include <type_traits>
#include <concepts>
#include <format>
#include <print>
#include <stdexcept>

std::string ReadFile(const char* path);
std::string ReadFile(const std::string& path);

namespace Core
{
	// Currently, this class does nothing
	// However, this class will be a part of the program's backbone later
	class Utility
	{
	public:
		Utility() = default;
		virtual ~Utility() = default;
	};
}

#endif
