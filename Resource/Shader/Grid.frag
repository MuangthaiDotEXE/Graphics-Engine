#version 460 core

layout(location = 0) out vec4 fragColor;

in vec3 worldPosition;

uniform float gridSize = 100.0f;
uniform vec3 cameraWorldPosition;
uniform float gridMinPixelsBetweenCells = 2.0f;
uniform float gridCellSize = 0.025f;
uniform vec4 gridColorThin = vec4(0.5f, 0.5f, 0.5f, 1.0f);
uniform vec4 gridColorThick = vec4(0.0f, 0.0f, 0.0f, 1.0f);

float log10(float x)
{
    float f = log(x) / log(10.0f);
    return f;
}

float satf(float x)
{
    float f = clamp(x, 0.0f, 1.0f);
    return f;
}

vec2 satv(vec2 x)
{
    vec2 v = clamp(x, vec2(0.0f), vec2(1.0f));
    return v;
}

float max2(vec2 vector)
{
    float f = max(vector.x, vector.y);
    return f;
}

void main()
{
    vec2 dvx = vec2(dFdx(worldPosition.x), dFdy(worldPosition.x));
    vec2 dvy = vec2(dFdx(worldPosition.z), dFdy(worldPosition.z));

    float lx = length(dvx);
    float ly = length(dvy);

    vec2 dudv = vec2(lx, ly);

    float l = length(dudv);

    float lod = max(0.0f, log10(l * gridMinPixelsBetweenCells / gridCellSize) + 1.0f);

    float gridCellSizeLOD0 = gridCellSize * pow(10.0f, floor(lod));
    float gridCellSizeLOD1 = gridCellSizeLOD0 * 10.0f;
    float gridCellSizeLOD2 = gridCellSizeLOD1 * 10.0f;

    dudv *= 4.0f;

    vec2 modulateResult = mod(worldPosition.xz, gridCellSizeLOD0) / dudv;
    float lodAlpha0 = max2(vec2(1.0f) - abs(satv(modulateResult) * 2.0f - vec2(1.0f)));

    modulateResult = mod(worldPosition.xz, gridCellSizeLOD1) / dudv;
    float lodAlpha1 = max2(vec2(1.0f) - abs(satv(modulateResult) * 2.0f - vec2(1.0f)));

    modulateResult = mod(worldPosition.xz, gridCellSizeLOD2) / dudv;
    float lodAlpha2 = max2(vec2(1.0f) - abs(satv(modulateResult) * 2.0f - vec2(1.0f)));

    float lodFade = fract(lod);

    vec4 color;
    if (lodAlpha2 > 0.0f)
    {
        color = gridColorThick;
        color.a *= lodAlpha2;
    }
    else
    {
        if (lodAlpha1 > 0.0f)
        {
            color = mix(gridColorThick, gridColorThin, lodFade);
            color.a *= lodAlpha1;
        }
        else
        {
            color = gridColorThin;
            color.a *= (lodAlpha0 * (1.0f - lodFade));
        }
    }

    float opacityFalloff = (1.0f - satf(length(worldPosition.xz - cameraWorldPosition.xz) / gridSize));
    color.a *= opacityFalloff;

    fragColor = color;
}
