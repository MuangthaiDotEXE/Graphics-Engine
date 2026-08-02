#version 460 core

out vec4 fragColor;

in vec3 nearPoint;
in vec3 farPoint;

uniform mat4 view;
uniform mat4 projection;
uniform float nearPlane;
uniform float farPlane;

const float FINE_CELL_SIZE = 1.0f;
const float COARSE_CELL_SIZE = 10.0f;

const vec3 FINE_COLOR = vec3(0.35f);
const vec3 COARSE_COLOR = vec3(0.55f);
const float LINE_WIDTH = 0.4f;

const vec3 X_AXIS_COLOR = vec3(0.84f, 0.18f, 0.18f);
const vec3 Y_AXIS_COLOR = vec3(0.18f, 0.84f, 0.18f);
const vec3 Z_AXIS_COLOR = vec3(0.18f, 0.38f, 0.84f);
const float AXIS_WIDTH = 2.0f;

const float FADE_START = 0.35f;
const float FADE_END = 0.60f;

float ToDepthBuffer(vec3 worldPosition)
{
    vec4 clip = projection * view * vec4(worldPosition, 1.0f);
    return (clip.z / clip.w) * 0.5f + 0.5f;
}

float LinearDepth(vec3 worldPosition)
{
    vec4 clip = projection * view * vec4(worldPosition, 1.0f);
    float ndcDepth = (clip.z / clip.w) * 2.0f - 1.0f;
    float linear = (2.0f * nearPlane * farPlane) /
                     (farPlane + nearPlane - ndcDepth * (farPlane - nearPlane));
    return linear / farPlane;
}

float GridAlpha(vec3 worldPosition, float cellSize)
{
    vec2 coord = worldPosition.xz / cellSize;
    vec2 deriv = fwidth(coord);
    vec2 grid = abs(fract(coord - 0.5f) - 0.5f) / deriv;
    float line = min(grid.x, grid.y);
    return 1.0f - min(line / LINE_WIDTH, 1.0f);
}

void main()
{
    vec3 rayDir = normalize(farPoint - nearPoint);
    
    float dxz2 = rayDir.x * rayDir.x + rayDir.z * rayDir.z;
    float tY = (dxz2 > 1e-6f)
                       ? -(nearPoint.x * rayDir.x + nearPoint.z * rayDir.z) / dxz2
                       : -1.0f;
    vec3 yClosest = nearPoint + tY * rayDir;
    float yDistXZ = (tY > 0.0f) ? length(yClosest.xz) : 1e9f;
    float yPixWidth = (tY > 0.0f) ? length(fwidth(yClosest.xz)) : 1.0f;
    float yAxisCov = (tY > 0.0f)
                       ? max(0.0f, 1.0f - yDistXZ / max(yPixWidth * AXIS_WIDTH, 1e-6f))
                       : 0.0f;
    
    float t = -nearPoint.y / (farPoint.y - nearPoint.y);
    bool gridHit = (t > 0.0f);
    bool yHit = (tY > 0.0f && yAxisCov > 0.0f);

    if (!gridHit && !yHit) discard;

    float alpha = 0.0f;
    vec3 color = vec3(0.0f);
    float depthValue = 1.0f;

    if (gridHit)
    {
        vec3 hitPos = nearPoint + t * (farPoint - nearPoint);
        float linD = LinearDepth(hitPos);
        float fade = 1.0f - smoothstep(FADE_START, FADE_END, linD);

        if (fade > 0.0f)
        {
            float fineA = GridAlpha(hitPos, FINE_CELL_SIZE);
            float coarseA = GridAlpha(hitPos, COARSE_CELL_SIZE);

            alpha = max(fineA, coarseA) * fade;
            color = (coarseA >= fineA) ? COARSE_COLOR : FINE_COLOR;

            vec2 deriv = fwidth(hitPos.xz);
            float xCov = 1.0f - min(abs(hitPos.z) / (deriv.y * AXIS_WIDTH), 1.0f);
            float zCov = 1.0f - min(abs(hitPos.x) / (deriv.x * AXIS_WIDTH), 1.0f);

            if (xCov > 0.0f) { color = mix(color, X_AXIS_COLOR, xCov); alpha = max(alpha, xCov * fade); }
            if (zCov > 0.0f) { color = mix(color, Z_AXIS_COLOR, zCov); alpha = max(alpha, zCov * fade); }

            depthValue = ToDepthBuffer(hitPos);
        }
    }

    if (yHit)
    {
        float yLinD = LinearDepth(yClosest);
        float yFade = 1.0f - smoothstep(FADE_START, FADE_END, yLinD);
        float yAlpha = yAxisCov * yFade;

        if (yAlpha > 0.0f)
        {
            if (yAlpha > alpha)
                depthValue = ToDepthBuffer(yClosest);

            color = mix(color, Y_AXIS_COLOR, yAlpha);
            alpha = max(alpha, yAlpha);
        }
    }

    if (alpha <= 0.0f) discard;

    gl_FragDepth = depthValue;
    fragColor = vec4(color, alpha);
}
