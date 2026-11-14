set(SOURCES
	"Source/Main.cpp"
	"Source/Manager.h"
	"Source/Manager.cpp"
)

add_executable(Manager)
target_sources(Manager PRIVATE ${SOURCES})

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SOURCES})

target_compile_definitions(Manager
	PRIVATE
	ProjectDirectory=\"${PROJECT_SOURCE_DIR}\"
	ManagerDirectory=\"${PROJECT_SOURCE_DIR}/Manager\"

	PRIVATE
	GLFW_INCLUDE_NONE
)

target_link_libraries(Manager Core)
target_include_directories(Manager PRIVATE "Source")

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
