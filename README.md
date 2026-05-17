<div align="center">
	<h1> Graphics Engine </h1>
	<h3> Graphics Engine written in C++ </h3>
	<p> Using GLFW, GLAD OpenGL, STB image, GLM and more </p>
	<img alt="GitHub top language" src="https://img.shields.io/github/languages/top/MuangthaiDotEXE/Graphics-Engine">
	<img alt="GitHub License" src="https://img.shields.io/github/license/MuangthaiDotEXE/Graphics-Engine">
	<img alt="GitHub last commit" src="https://img.shields.io/github/last-commit/MuangthaiDotEXE/Graphics-Engine">
	<img alt="GitHub Actions Workflow Status" src="https://img.shields.io/github/actions/workflow/status/MuangthaiDotEXE/Graphics-Engine/cmake-multi-platform.yml">
	<p></p>
	<img src="Icon.png" alt="Icon">
</div>

### Features
- Multi-platform windowing system
- 3 dimensional OpenGL graphics API rendering system with simple lighting (Directional light, spot light and point light) 
- Simple image texture support (Nearest filter)
- Basic 3 dimensional camera system with perspective and orthographic projection and with euler and quaternion rotation
- Basic input system for controlling window and graphics rendering
- Simple user interface rendering
- Automate libraries package finding

### Future Plans
- Add advanced OpenGL graphics API rendering
- Add and update Vulkan graphics API rendering
- Add advanced user interface with Dear ImGui
- Add advanced and flexible input system with mouse and keyboard input
- Add audio system using openAL
- Fully automate libraries package finding and installation with CMake

### Screenshot
<div align="center">
	<img src="Asset/Image/Screenshot 1.png" alt="Screenshot 1">
</div>
(Screenshot taken: 2026-05-17 7:26 UTC)

### How to use
- Clone the repository using `git clone` command
- Run `Build.py` using Python. For platform specific, run `Build.bat` (Microsoft Windows) or  `Build.sh` (Unix)
- Once the project is built successfully, the project should be ready to go

### Credits
- This Graphics Engine project follows [VictorGordan's Youtube OpenGL tutorial playlist](https://youtube.com/playlist?list=PLPaoO-vpZnumdcb4tZc4x5Q-v7CkrQ6M-&si=UxJGYZ8omvecyZBD) and [LearnOpenGL tutorial](https://learnopengl.com/). Huge shoutout to them
- For more information about contributors and their roles. Please refer to [CREDITS.md](CREDITS.md)

### License
- For more information about license. Please refer to [LICENSE.txt](LICENSE.txt)
