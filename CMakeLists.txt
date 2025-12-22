cmake_minimum_required(VERSION 3.20)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

project(GraphicsEngine)

include("Library.cmake")

add_subdirectory(App)
add_subdirectory(Engine)
