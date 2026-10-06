cmake_minimum_required(VERSION 3.20)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
set(CMAKE_CXX_EXTENSIONS ON)

project("Graphics Engine" 
		VERSION 1.0.0 
		LANGUAGES C CXX
		DESCRIPTION "Graphics Engine made in C++"
)

message("-- Building project: ${PROJECT_NAME} ${PROJECT_VERSION}")

include("Library.cmake")

add_subdirectory(Core)
add_subdirectory(Engine)
