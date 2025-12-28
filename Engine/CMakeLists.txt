set(SOURCES
	"Source/Main.cpp"
	"Source/Engine.h"
	"Source/Engine.cpp"
	"Source/Graphics/Mesh/Mesh.h"
	"Source/Graphics/Mesh/Mesh.cpp"
	"Source/Graphics/Mesh/Shader.h"
	"Source/Graphics/Mesh/Shader.cpp"
	"Source/Graphics/Mesh/VAO.h"
	"Source/Graphics/Mesh/VAO.cpp"
	"Source/Graphics/Mesh/VBO.h"
	"Source/Graphics/Mesh/VBO.cpp"
	"Source/Graphics/Mesh/EBO.h"
	"Source/Graphics/Mesh/EBO.cpp"
	"Source/Graphics/Camera/Camera.h"
	"Source/Graphics/Camera/Camera.cpp"
)

add_executable(Engine)
target_sources(Engine PRIVATE ${SOURCES})

add_definitions(-DProjectDirectory=\"${PROJECT_SOURCE_DIR}\")

source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${SOURCES})

add_compile_definitions(
	GLFW_INCLUDE_NONE
	GLM_ENABLE_EXPERIMENTAL
)

target_link_libraries(Engine App)

target_include_directories(Engine PRIVATE "Source")

set_target_properties(Engine PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/Engine")
