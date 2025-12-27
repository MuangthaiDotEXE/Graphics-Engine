set(SOURCES
	"Source/Main.cpp"
	"Source/Engine.h"
	"Source/Engine.cpp"
	"Source/Graphics/Mesh.h"
	"Source/Graphics/Mesh.cpp"
	"Source/Graphics/Shader.h"
	"Source/Graphics/Shader.cpp"
	"Source/Graphics/VAO.h"
	"Source/Graphics/VAO.cpp"
	"Source/Graphics/VBO.h"
	"Source/Graphics/VBO.cpp"
	"Source/Graphics/EBO.h"
	"Source/Graphics/EBO.cpp"
)

add_executable(Engine)
target_sources(Engine PRIVATE ${SOURCES})

source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${SOURCES})

target_link_libraries(Engine App)

target_include_directories(Engine PRIVATE "Source")

set_target_properties(Engine PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/Engine")
