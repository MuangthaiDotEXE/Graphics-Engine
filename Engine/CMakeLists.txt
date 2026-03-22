set(SOURCES
	"Source/Main.cpp"
	"Source/Engine.h"
	"Source/Engine.cpp"
	"Source/Graphics/World.h"
	"Source/Graphics/World.cpp"
	"Source/Graphics/Mesh/Mesh.h"
	"Source/Graphics/Mesh/Mesh.cpp"
	"Source/Graphics/Mesh/Cube.h"
	"Source/Graphics/Mesh/Cube.cpp"
	"Source/Graphics/Mesh/Plane.h"
	"Source/Graphics/Mesh/Plane.cpp"
	"Source/Graphics/Camera/Camera.h"
	"Source/Graphics/Camera/Camera.cpp"
	"Source/Graphics/Light/Light.h"
	"Source/Graphics/Light/Light.cpp"
)

add_executable(Engine)
target_sources(Engine PRIVATE ${SOURCES})

add_definitions(-DProjectDirectory=\"${PROJECT_SOURCE_DIR}\")

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SOURCES})

add_compile_definitions(
	GLFW_INCLUDE_NONE
	GLM_ENABLE_EXPERIMENTAL
)

target_link_libraries(Engine Core)
target_include_directories(Engine PRIVATE "Source")

if (MSVC)
	set_target_properties(Engine PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/Engine")
endif()
