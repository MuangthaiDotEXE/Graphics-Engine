set(SOURCES
	"Source/Main.cpp"
	"Source/Engine.h"
	"Source/Engine.cpp"
	"Source/Timer/Timer.h"
	"Source/Timer/Timer.cpp"
	"Source/Graphics/Sky/Sky.h"
	"Source/Graphics/Sky/Sky.cpp"
	"Source/Graphics/Grid/Grid.h"
	"Source/Graphics/Grid/Grid.cpp"
	"Source/Graphics/Scene/Scene.h"
	"Source/Graphics/Scene/Scene.cpp"
	"Source/Graphics/Scene/Sample.h"
	"Source/Graphics/Scene/Sample.cpp"
	"Source/Graphics/Scene/World.h"
	"Source/Graphics/Scene/World.cpp"
	"Source/Graphics/Scene/Space.h"
	"Source/Graphics/Scene/Space.cpp"
	"Source/Graphics/Object/Mesh/Mesh.h"
	"Source/Graphics/Object/Mesh/Mesh.cpp"
	"Source/Graphics/Object/Mesh/Cube.h"
	"Source/Graphics/Object/Mesh/Cube.cpp"
	"Source/Graphics/Object/Mesh/Sphere.h"
	"Source/Graphics/Object/Mesh/Sphere.cpp"
	"Source/Graphics/Object/Mesh/Pyramid.h"
	"Source/Graphics/Object/Mesh/Pyramid.cpp"
	"Source/Graphics/Object/Mesh/Plane.h"
	"Source/Graphics/Object/Mesh/Plane.cpp"
	"Source/Graphics/Object/Mesh/Quad.h"
	"Source/Graphics/Object/Mesh/Quad.cpp"
	"Source/Graphics/Object/Mesh/Triangle.h"
	"Source/Graphics/Object/Mesh/Triangle.cpp"
	"Source/Graphics/Object/Model/Model.h"
	"Source/Graphics/Object/Model/Model.cpp"
	"Source/Graphics/Object/Camera/Camera.h"
	"Source/Graphics/Object/Camera/Camera.cpp"
	"Source/Graphics/Object/Light/Light.h"
	"Source/Graphics/Object/Light/Light.cpp"
)

add_executable(Engine)
target_sources(Engine PRIVATE ${SOURCES})

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SOURCES})

target_compile_definitions(Engine PRIVATE
	ProjectDirectory=\"${PROJECT_SOURCE_DIR}\"
	EngineDirectory=\"${PROJECT_SOURCE_DIR}/Engine\"
)

target_compile_definitions(Engine PRIVATE
	GLFW_INCLUDE_NONE
	GLM_ENABLE_EXPERIMENTAL
)

target_link_libraries(Engine Core)
target_include_directories(Engine PRIVATE "Source")

if (MSVC)
	set_target_properties(Engine 
						  PROPERTIES 
						  VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/Engine"
	)
endif()

if (WIN32)
	set_target_properties(Engine
						  PROPERTIES
						  WIN32_EXECUTABLE $<OR:$<CONFIG:Release>,$<CONFIG:MinSizeRel>>
	)

	if (MSVC)
		target_link_options(Engine 
							PRIVATE
							$<$<OR:$<CONFIG:Release>,$<CONFIG:MinSizeRel>>:/ENTRY:mainCRTStartup>
		)
	endif()
endif()
