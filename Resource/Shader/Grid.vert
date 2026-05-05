#version 460 core

out vec3 worldPosition;

uniform mat4 verticesPosition = mat4(1.0f);
uniform float gridSize = 100.0f;
uniform vec3 cameraWorldPosition;

const vec3 position[4] = vec3[4]
(
	vec3(-1.0f, 0.0f, -1.0f),
	vec3( 1.0f, 0.0f, -1.0f),
	vec3( 1.0f, 0.0f,  1.0f),
	vec3(-1.0f, 0.0f,  1.0f)
);

const int indices[6] = int[6]
(
	0, 1, 2,
	1, 2, 3
);

void main()
{
	int index = indices[gl_VertexID];
	vec3 currentPosition = position[index] * gridSize;
	currentPosition.x += cameraWorldPosition.x;
	currentPosition.z += cameraWorldPosition.z;

	vec4 positions = vec4(currentPosition, 1.0f);

	gl_Position = verticesPosition * positions;

	worldPosition = currentPosition;
}
