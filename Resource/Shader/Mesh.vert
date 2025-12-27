#version 460 core

layout (location = 0) in vec3 meshPosition;
layout (location = 1) in vec3 meshColor;

out vec3 color;

void main()
{
	gl_Position = vec4(meshPosition, 1.0f);

	color = meshColor;
}
