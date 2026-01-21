set(SOURCES
	 "Source/App.h" 
	 "Source/App.cpp" 
	 "Source/Window.h" 
	 "Source/Window.cpp"
	 "Source/Graphics.h" 
	 "Source/Graphics.cpp"
	 "Source/OpenGL.h" 
	 "Source/OpenGL.cpp"
	 "Source/Vulkan.h" 
	 "Source/Vulkan.cpp"
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
	 "Source/UserInterface.h"
	 "Source/UserInterface.cpp"
)

add_library(Core STATIC)
target_sources(Core PRIVATE ${SOURCES})

source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${SOURCES})

add_compile_definitions(
	GLFW_INCLUDE_NONE
	GLM_ENABLE_EXPERIMENTAL
)

add_library(glad "${CMAKE_SOURCE_DIR}/Library/glad/src/gl.c" "${CMAKE_SOURCE_DIR}/Library/glad/src/vulkan.c")

target_link_libraries(Core glfw)
target_link_libraries(Core OpenGL::GL)
target_link_libraries(Core Vulkan::Vulkan)
target_link_libraries(Core glad)
target_link_libraries(Core glm)

target_include_directories(Core PUBLIC "Source") 