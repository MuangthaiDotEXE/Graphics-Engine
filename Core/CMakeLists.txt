set(SOURCES
	 "Source/App.h" 
	 "Source/App.cpp" 
	 "Source/Window/Window.h" 
	 "Source/Window/Window.cpp"
	 "Source/Graphics/Graphics.h" 
	 "Source/Graphics/Graphics.cpp"
	 "Source/Graphics/OpenGL.h" 
	 "Source/Graphics/OpenGL.cpp"
	 "Source/Graphics/Vulkan.h" 
	 "Source/Graphics/Vulkan.cpp"
	 "Source/Graphics/Shader/Shader.h"
	 "Source/Graphics/Shader/Shader.cpp"
	 "Source/Graphics/Shader/VAO.h"
	 "Source/Graphics/Shader/VAO.cpp"
	 "Source/Graphics/Shader/VBO.h"
	 "Source/Graphics/Shader/VBO.cpp"
	 "Source/Graphics/Shader/EBO.h"
	 "Source/Graphics/Shader/EBO.cpp"
	 "Source/Graphics/Texture/Texture.h"
	 "Source/Graphics/Texture/Texture.cpp"
	 "Source/Graphics/Texture/stb.cpp"
	 "Source/Graphics/Model/Model.h"
	 "Source/Graphics/Model/Model.cpp"
	 "Source/UserInterface/UserInterface.h"
	 "Source/UserInterface/UserInterface.cpp"
	 "Source/Utility/Utility.h"
	 "Source/Utility/Utility.cpp"
)

add_library(Core STATIC)
target_sources(Core PRIVATE ${SOURCES})

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SOURCES})

add_compile_definitions(
	GLFW_INCLUDE_NONE
	GLM_ENABLE_EXPERIMENTAL
)

add_library(glad "${CMAKE_SOURCE_DIR}/Library/glad/src/gl.c")

target_link_libraries(Core glfw OpenGL::GL Vulkan::Vulkan glad glm imgui imguizmo)
target_include_directories(Core PUBLIC "Source") 
