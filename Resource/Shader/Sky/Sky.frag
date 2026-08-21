#version 460 core

out vec4 fragColor;

in vec3 textureCoordinate;

uniform samplerCube skySampler;

void main()
{
    fragColor = texture(skySampler, textureCoordinate);
}
