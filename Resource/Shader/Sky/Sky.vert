#version 460 core

layout (location = 0) in vec3 positions;

out vec3 textureCoordinate;

uniform mat4 view;
uniform mat4 projection;

void main()
{
    vec4 position = projection * view * vec4(positions, 1.0f);
    gl_Position = vec4(position.x, position.y, position.w, position.w);

    textureCoordinate = vec3(positions.x, positions.y, -positions.z);
}
