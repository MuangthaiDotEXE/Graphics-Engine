#pragma once

#ifndef UTILITY_H
#define UTILITY_H

#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include <type_traits>
#include <concepts>
#include <print>
#include <stdexcept>

std::string ReadFile(const char* path);
std::string ReadFile(const std::string& path);

namespace Core
{
	class Utility
	{
	public:
		Utility();
		virtual ~Utility();
	};
}

#endif
