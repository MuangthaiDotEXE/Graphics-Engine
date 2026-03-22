include(FetchContent)

find_package(glf3 QUIET)
if (NOT glfw3_FOUND)
	set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
	set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
	set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

	FetchContent_Declare(
		glfw3
		DOWNLOAD_EXTRACT_TIMESTAMP OFF
		URL https://github.com/glfw/glfw/releases/download/3.4/glfw-3.4.zip
	)

	FetchContent_MakeAvailable(glfw3)
endif()

find_package(OpenGL REQUIRED)
find_package(Vulkan REQUIRED)

include_directories(
	"Library/glad/include"
	"Library/nlohmann/include"
)

FetchContent_Declare(
	stb
	GIT_REPOSITORY https://github.com/nothings/stb.git
	GIT_TAG master
)

FetchContent_MakeAvailable(stb)

include_directories("${stb_SOURCE_DIR}")

find_package(glm QUIET)
if (NOT glm_FOUND)
	FetchContent_Declare(
		glm
		DOWNLOAD_EXTRACT_TIMESTAMP OFF
		URL https://github.com/g-truc/glm/releases/download/1.0.3/glm-1.0.3.zip
	)

	FetchContent_MakeAvailable(glm)
endif()

FetchContent_Declare(
	imgui
	GIT_REPOSITORY https://github.com/ocornut/imgui.git
	GIT_TAG docking
)

FetchContent_MakeAvailable(imgui)

add_library(imgui STATIC
	"${imgui_SOURCE_DIR}/imgui.cpp"
	"${imgui_SOURCE_DIR}/imgui_draw.cpp"
	"${imgui_SOURCE_DIR}/imgui_tables.cpp"
	"${imgui_SOURCE_DIR}/imgui_widgets.cpp"
	"${imgui_SOURCE_DIR}/imgui_demo.cpp"
	"${imgui_SOURCE_DIR}/backends/imgui_impl_glfw.cpp"
	"${imgui_SOURCE_DIR}/backends/imgui_impl_opengl3.cpp"
)

target_include_directories(imgui PUBLIC "${imgui_SOURCE_DIR}" "${imgui_SOURCE_DIR}/backends")
target_link_libraries(imgui PUBLIC glfw OpenGL::GL Vulkan::Vulkan)
target_compile_definitions(imgui PRIVATE GLFW_INCLUDE_NONE)
set_target_properties(imgui PROPERTIES FOLDER "Library")

FetchContent_Declare(
	imguizmo
	GIT_REPOSITORY https://github.com/CedricGuillemet/ImGuizmo.git
	GIT_TAG master
)

FetchContent_MakeAvailable(imguizmo)

add_library(imguizmo STATIC "${imguizmo_SOURCE_DIR}/ImGuizmo.cpp")

target_include_directories(imguizmo PUBLIC "${imguizmo_SOURCE_DIR}")
target_link_libraries(imguizmo PUBLIC imgui)
set_target_properties(imguizmo PROPERTIES FOLDER "Library")
