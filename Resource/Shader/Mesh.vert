#version 460 core

layout (location = 0) in vec3 meshPosition;
layout (location = 1) in vec3 meshColor;
layout (location = 2) in vec2 meshTexture;

out vec3 color;
out vec2 textureCoordinate;

uniform mat4 model;
uniform mat4 cameraMatrix;

void main()
{
	gl_Position = cameraMatrix * model * vec4(meshPosition, 1.0f);

	color = meshColor;
	textureCoordinate = meshTexture;
}
