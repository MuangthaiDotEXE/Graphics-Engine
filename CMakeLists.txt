cmake_minimum_required(VERSION 3.20)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

project(GraphicsEngine 
		VERSION 1.0.0 
		LANGUAGES C CXX
		DESCRIPTION "Graphics Engine made in C++"
)

include("Library.cmake")

add_subdirectory(Core)
add_subdirectory(Engine)
