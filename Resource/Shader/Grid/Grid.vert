#version 460 core

layout (location = 0) in vec2 positions;

uniform mat4 view;
uniform mat4 projection;

out vec3 nearPoint;
out vec3 farPoint;

vec3 Unproject(float x, float y, float z)
{
	mat4 viewInverse = inverse(view);
	mat4 projectionInverse = inverse(projection);

	vec4 worldPosition = viewInverse * projectionInverse * vec4(x, y, z, 1.0f);
	return worldPosition.xyz / worldPosition.w;
}

void main()
{
    nearPoint = Unproject(positions.x, positions.y, 0.0f);
    farPoint = Unproject(positions.x, positions.y, 1.0f);

    gl_Position = vec4(positions, 0.0f, 1.0f);
}
