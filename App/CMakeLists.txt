set(SOURCES
	 "Source/App.h" 
	 "Source/App.cpp" 
	 "Source/Window.h" 
	 "Source/Window.cpp"
	 "Source/Graphics.h" 
	 "Source/Graphics.cpp"
	 "Source/Shader.h"
	 "Source/Shader.cpp"
	 "Source/VAO.h"
	 "Source/VAO.cpp"
	 "Source/VBO.h"
	 "Source/VBO.cpp"
	 "Source/EBO.h"
	 "Source/EBO.cpp"
	 "Source/Texture.h"
	 "Source/Texture.cpp"
	 "Source/stb.cpp"
)

add_library(App STATIC)
target_sources(App PRIVATE ${SOURCES})

source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${SOURCES})

add_compile_definitions(
	GLFW_INCLUDE_NONE
	GLM_ENABLE_EXPERIMENTAL
)

add_library(glad "${CMAKE_SOURCE_DIR}/Library/glad/src/gl.c")

target_link_libraries(App glfw)
target_link_libraries(App OpenGL::GL)
target_link_libraries(App glad)
target_link_libraries(App glm)

target_include_directories(App PUBLIC "Source") 