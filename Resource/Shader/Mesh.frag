#version 460 core

out vec4 fragColor;

in vec3 color;
in vec2 textureCoordinate;
in vec3 normal;
in vec3 currentPosition;

uniform sampler2D textureSampler;
uniform vec4 lightColor;
uniform vec3 lightPosition;
uniform float lightIntensity;
uniform vec3 cameraPosition;

void main()
{
	float ambient = 0.2f;

	vec3 normalizedNormal = normalize(normal);
	vec3 lightDirection = normalize(lightPosition - currentPosition);

	float diffuse = max(dot(normalizedNormal, lightDirection), 0.0f);

	float specularLight = 0.5f;
	vec3 viewDirection = normalize(cameraPosition - currentPosition);
	vec3 reflectDirection = reflect(-lightDirection, normalizedNormal);
	float specularAmount = pow(max(dot(viewDirection, reflectDirection), 0.0f), 8);
	float specular = specularAmount * specularLight;

	vec4 light = lightColor * lightIntensity;

	//fragColor = vec4(color, 1.0f) * light * (diffuse + ambient + specular);
	fragColor = texture(textureSampler, textureCoordinate) * light * (diffuse + ambient + specular);
}
