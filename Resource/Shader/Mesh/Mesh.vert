#version 460 core

layout (location = 0) in vec3 positions;
layout (location = 1) in vec3 colors;
layout (location = 2) in vec2 textures;
layout (location = 3) in vec3 normals;

out vec3 color;
out vec2 textureCoordinate;
out vec3 normal;
out vec3 currentPosition;

uniform mat4 model;
uniform mat4 cameraMatrix;

void main()
{
	currentPosition = vec3(model * vec4(positions, 1.0f));
	gl_Position = cameraMatrix * vec4(currentPosition, 1.0f);

	color = colors;
	textureCoordinate = textures;
	normal = normals;
}
