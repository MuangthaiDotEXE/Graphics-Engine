#version 460 core

layout (location = 0) in vec3 positions;
layout (location = 1) in vec3 normals;

uniform mat4 model;
uniform mat4 translation;
uniform mat4 rotation;
uniform mat4 scale;
uniform mat4 cameraMatrix;
uniform float outline;

void main()
{
	vec3 currentPosition = vec3(model * translation * rotation * scale * vec4(positions * normals * outline, 1.0f));
	gl_Position = cameraMatrix * vec4(currentPosition, 1.0f);
}
