set(SOURCES
	"Source/Main.cpp"
)

add_executable(Engine)
target_sources(Engine PRIVATE ${SOURCES})

target_link_libraries(Engine App)

target_include_directories(Engine PRIVATE "Source")

set_target_properties(Engine PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/Engine")
