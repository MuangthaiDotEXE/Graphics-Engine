#include "Selection.h"

const float selectionCorners[] =
{
    -0.5f, -0.5f, -0.5f,
     0.5f, -0.5f, -0.5f,
     0.5f,  0.5f, -0.5f,
    -0.5f,  0.5f, -0.5f,
    -0.5f, -0.5f,  0.5f,
     0.5f, -0.5f,  0.5f,
     0.5f,  0.5f,  0.5f,
    -0.5f,  0.5f,  0.5f
};

const GLuint selectionEdges[] =
{
    0, 1, 1, 2, 2, 3, 3, 0,    // Back
    4, 5, 5, 6, 6, 7, 7, 4,    // Front
    0, 4, 1, 5, 2, 6, 3, 7     // Connecting
};

static void GetPaddedBounds(const Engine::Mesh& mesh, glm::vec3& outMin, glm::vec3& outMax)
{
    const float minExtent = 0.02f;
    outMin = mesh.boundsMin;
    outMax = mesh.boundsMax;

    for (size_t i = 0; i < 3; ++i)
    {
        if (outMax[i] - outMin[i] < minExtent)
        {
            const float center = (outMax[i] + outMin[i]) * 0.5f;
            outMin[i] = center - minExtent * 0.5f;
            outMax[i] = center + minExtent * 0.5f;
        }
    }
}

Engine::Selection::Selection()
    : outlineShader(ProjectDirectory "/Resource/Shader/Selection/Selection.vert", ProjectDirectory "/Resource/Shader/Selection/Selection.frag")
{
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ebo);

    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(selectionCorners), selectionCorners, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(selectionEdges), selectionEdges, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

Engine::Selection::~Selection()
{
    glDeleteBuffers(1, &ebo);
    glDeleteBuffers(1, &vbo);
    glDeleteVertexArrays(1, &vao);
}

void Engine::Selection::Update(GLFWwindow* window, const glm::mat4& view, const glm::mat4& projection, const glm::vec2& viewportPosition, const glm::vec2& viewportSize, const std::vector<std::unique_ptr<Mesh>>& meshes, bool inputAllowed)
{
    const bool mouseDown = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS;
    const bool clicked = mouseDown && !wasMouseDown;
    wasMouseDown = mouseDown;

    if (!clicked || !inputAllowed || viewportSize.x <= 0.0f || viewportSize.y <= 0.0f)
    {
        return;
    }

    double mouseX, mouseY;
    glfwGetCursorPos(window, &mouseX, &mouseY);

    const glm::vec2 local = glm::vec2((float)mouseX, (float)mouseY) - viewportPosition;
    if (local.x < 0.0f || local.y < 0.0f || local.x > viewportSize.x || local.y > viewportSize.y)
    {
        return;
    }

    const float ndcX = 2.0f * local.x / viewportSize.x - 1.0f;
    const float ndcY = 1.0f - 2.0f * local.y / viewportSize.y;

    const glm::mat4 inverseViewProjection = glm::inverse(projection * view);
    glm::vec4 nearPoint = inverseViewProjection * glm::vec4(ndcX, ndcY, -1.0f, 1.0f);
    glm::vec4 farPoint = inverseViewProjection * glm::vec4(ndcX, ndcY, 1.0f, 1.0f);
    nearPoint /= nearPoint.w;
    farPoint /= farPoint.w;

    Ray ray{ glm::vec3(nearPoint), glm::normalize(glm::vec3(farPoint - nearPoint)) };

    struct Hit
    {
        Mesh* mesh;
        float t;
    };
    std::vector<Hit> hits;

    for (const auto& mesh : meshes)
    {
        float t;
        if (IntersectLocalBox(*mesh, ray, t))
        {
            hits.push_back({ mesh.get(), t });
        }
    }

    std::sort(hits.begin(), hits.end(), [](const Hit& a, const Hit& b)
        {
            return a.t < b.t;
        }
    );

    if (hits.empty())
    {
        selected = nullptr;
        return;
    }

    if (reclickMode == ReclickMode::SELECTBEHIND && hits[0].mesh == selected && hits.size() > 1)
    {
        selected = hits[1].mesh;
        return;
    }

    selected = hits[0].mesh;
}

void Engine::Selection::DrawOutline(Camera& camera)
{
    if (!selected)
    {
        return;
    }

    glm::vec3 boundsMin, boundsMax;
    GetPaddedBounds(*selected, boundsMin, boundsMax);

    const glm::mat4 boxMatrix = selected->transform.GetMatrix() * glm::translate(glm::mat4(1.0f), (boundsMin + boundsMax) * 0.5f) * glm::scale(glm::mat4(1.0f), boundsMax - boundsMin);

    outlineShader.Activate();
    glUniformMatrix4fv(glGetUniformLocation(outlineShader.programID, "model"), 1, GL_FALSE, &boxMatrix[0][0]);
    glUniform4f(glGetUniformLocation(outlineShader.programID, "color"), outlineColor.r, outlineColor.g, outlineColor.b, outlineColor.a);
    camera.Matrix(outlineShader, "cameraMatrix");

    glDisable(GL_DEPTH_TEST);
    glLineWidth(2.0f);

    glBindVertexArray(vao);
    glDrawElements(GL_LINES, 24, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);

    glEnable(GL_DEPTH_TEST);
}

Engine::Mesh* Engine::Selection::Get() const
{
    return selected;
}

void Engine::Selection::Clear()
{
    selected = nullptr;
}

bool Engine::Selection::IntersectLocalBox(const Mesh& mesh, const Ray& worldRay, float& outT)
{
    const glm::mat4 inverseModel = glm::inverse(mesh.transform.GetMatrix());
    const glm::vec3 origin = glm::vec3(inverseModel * glm::vec4(worldRay.origin, 1.0f));
    const glm::vec3 direction = glm::vec3(inverseModel * glm::vec4(worldRay.direction, 0.0f));

    glm::vec3 boundsMin, boundsMax;
    GetPaddedBounds(mesh, boundsMin, boundsMax);

    float tMin = -std::numeric_limits<float>::max();
    float tMax = std::numeric_limits<float>::max();

    for (size_t i = 0; i < 3; ++i)
    {
        if (std::abs(direction[i]) < 1e-8f)
        {
            if (origin[i] < boundsMin[i] || origin[i] > boundsMax[i])
            {
                return false;
            }
        }
        else
        {
            float t1 = (boundsMin[i] - origin[i]) / direction[i];
            float t2 = (boundsMax[i] - origin[i]) / direction[i];
            if (t1 > t2)
            {
                std::swap(t1, t2);
            }

            tMin = std::max(tMin, t1);
            tMax = std::min(tMax, t2);
            if (tMin > tMax)
            {
                return false;
            }
        }
    }

    if (tMax < 0.0f)
    {
        return false;
    }

    outT = tMin >= 0.0 ? tMin : tMax;
    return true;
}
