#version 460 core

out vec4 fragColor;

in vec3 color;
in vec2 textureCoordinate;
in vec3 normal;
in vec3 currentPosition;

uniform sampler2D textureSampler;
uniform sampler2D specularMapSampler;
uniform vec4 lightColor;
uniform vec3 lightPosition;
uniform float lightIntensity;
uniform vec3 cameraPosition;

vec4 directLight()
{
	float ambient = 0.2f;

	vec3 normalizedNormal = normalize(normal);
	vec3 lightDirection = normalize(vec3(1.0f, 1.0f, 0.0f));

	float diffuse = max(dot(normalizedNormal, lightDirection), 0.0f);

	float specularLight = 0.5f;
	vec3 viewDirection = normalize(cameraPosition - currentPosition);
	vec3 reflectDirection = reflect(-lightDirection, normalizedNormal);
	float specularAmount = pow(max(dot(viewDirection, reflectDirection), 0.0f), 8);
	float specular = specularAmount * specularLight;

	vec4 light = lightColor * lightIntensity;

	return texture(textureSampler, textureCoordinate) * light * (diffuse + ambient) + texture(specularMapSampler, textureCoordinate).r * specular;
}

vec4 pointLight()
{
	vec3 lightVector = lightPosition - currentPosition;
	float distance = length(lightVector);
	float a = 0.05f;
	float b = 0.01f;
	float intensity = 1.0f / (a * distance * distance + b * distance + 1.0f);

	float ambient = 0.2f;

	vec3 normalizedNormal = normalize(normal);
	vec3 lightDirection = normalize(lightVector);

	float diffuse = max(dot(normalizedNormal, lightDirection), 0.0f);

	float specularLight = 0.5f;
	vec3 viewDirection = normalize(cameraPosition - currentPosition);
	vec3 reflectDirection = reflect(-lightDirection, normalizedNormal);
	float specularAmount = pow(max(dot(viewDirection, reflectDirection), 0.0f), 8);
	float specular = specularAmount * specularLight;

	vec4 light = lightColor * lightIntensity;

	return texture(textureSampler, textureCoordinate) * light * (diffuse * intensity + ambient) + texture(specularMapSampler, textureCoordinate).r * specular * intensity;
}

vec4 spotLight()
{
	float outerCone = 0.90f;
	float innerCone = 0.95f;
	
	float ambient = 0.2f;

	vec3 normalizedNormal = normalize(normal);
	vec3 lightDirection = normalize(lightPosition - currentPosition);

	float diffuse = max(dot(normalizedNormal, lightDirection), 0.0f);

	float specularLight = 0.5f;
	vec3 viewDirection = normalize(cameraPosition - currentPosition);
	vec3 reflectDirection = reflect(-lightDirection, normalizedNormal);
	float specularAmount = pow(max(dot(viewDirection, reflectDirection), 0.0f), 8);
	float specular = specularAmount * specularLight;

	float angle = dot(vec3(0.0f, -1.0f, 0.0f), -lightDirection);
	float intensity = clamp((angle - outerCone) / (innerCone - outerCone), 0.0f, 1.0f);

	vec4 light = lightColor * lightIntensity;

	return texture(textureSampler, textureCoordinate) * light * (diffuse * intensity + ambient) + texture(specularMapSampler, textureCoordinate).r * specular * intensity;
}

void main()
{
	fragColor = pointLight();
}
