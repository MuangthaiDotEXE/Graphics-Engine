#version 460 core

layout (location = 0) in vec3 positions;

uniform mat4 model;
uniform mat4 cameraMatrix;

void main()
{
	gl_Position = cameraMatrix * model * vec4(positions, 1.0f);
}
