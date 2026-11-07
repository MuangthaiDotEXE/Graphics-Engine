#include "Gizmo.h"

void Engine::Gizmo::Draw(Mesh* mesh, Camera& camera, const glm::vec2& viewportPosition, const glm::vec2& viewportSize)
{
	ImGuizmo::BeginFrame();
	Keybinds();

	interacting = false;

	if (!mesh || mode == Mode::NONE || viewportSize.x <= 0.0f || viewportSize.y <= 0.0f)
	{
		return;
	}

	ImGuizmo::SetOrthographic(camera.GetProjectionMode() != Camera::ProjectionMode::PERSPECTIVE);
	ImGuizmo::SetDrawlist(ImGui::GetBackgroundDrawList());

	const ImGuiViewport* mainViewport = ImGui::GetMainViewport();
	ImGuizmo::SetRect(mainViewport->Pos.x + viewportPosition.x, mainViewport->Pos.y + viewportPosition.y, viewportSize.x, viewportSize.y);

	ImGuizmo::SetGizmoSizeClipSpace(size);
	ImGuizmo::AllowAxisFlip(false);

	ImGuizmo::OPERATION operation = ImGuizmo::TRANSLATE;
	float snapValue = snapTranslate;
	switch (mode)
	{
		case Mode::ROTATE:
			operation = ImGuizmo::ROTATE;
			snapValue = snapRotate;
			break;

		case Mode::SCALE:
			operation = ImGuizmo::SCALE;
			snapValue = snapScale;
			break;

		case Mode::TRANSFORM:
			operation = static_cast<ImGuizmo::OPERATION>(ImGuizmo::TRANSLATE | ImGuizmo::ROTATE | ImGuizmo::SCALEU);
			break;

		default:
			break;
	}

	const ImGuizmo::MODE space_ = space == Space::LOCAL || mode == Mode::SCALE ? ImGuizmo::LOCAL : ImGuizmo::WORLD;

	const bool snap = ImGui::GetIO().KeyCtrl;
	const float snapValues[3] = { snapValue, snapValue, snapValue };

	glm::mat4 view = camera.GetView();
	glm::mat4 projection = camera.GetProjection();
	glm::mat4 model = mesh->transform.GetMatrix();

	const bool changed = ImGuizmo::Manipulate(glm::value_ptr(view), glm::value_ptr(projection), operation, space_, glm::value_ptr(model), nullptr, snap && mode != Mode::TRANSFORM ? snapValues : nullptr);

	interacting = ImGuizmo::IsOver() || ImGuizmo::IsUsing();

	if (!changed)
	{
		return;
	}

	const glm::vec3 newPosition = glm::vec3(model[3]);
	const glm::vec3 newScale = glm::vec3(glm::length(glm::vec3(model[0])), glm::length(glm::vec3(model[1])), glm::length(glm::vec3(model[2])));

	bool applyPosition = mode == Mode::TRANSLATE;
	bool applyRotation = mode == Mode::ROTATE;
	bool applyScale = mode == Mode::SCALE;

	if (mode == Mode::TRANSFORM)
	{
		const float epsilon = 1e-4f;

		if (glm::distance(newPosition, mesh->transform.position) > epsilon)
		{
			applyPosition = true;
		}
		else if (glm::distance(newScale, mesh->transform.scale) > epsilon)
		{
			applyScale = true;
		}
		else
		{
			applyRotation = true;
		}
	}

	if (applyPosition)
	{
		mesh->transform.position = newPosition;
	}
	if (applyScale)
	{
		mesh->transform.scale = newScale;
	}
	if (applyRotation)
	{
		if (newScale.x < 1e-6f || newScale.y < 1e-6f || newScale.z < 1e-6f)
		{
			return;
		}

		const glm::mat3 r = glm::mat3(glm::vec3(model[0]) / newScale.x, glm::vec3(model[1]) / newScale.y, glm::vec3(model[2]) / newScale.z);

		float x, y, z;
		y = std::asin(std::clamp(r[2][0], -1.0f, 1.0f));
		if (std::abs(r[2][0]) < 0.99999f)
		{
			x = std::atan2(-r[2][1], r[2][2]);
			z = std::atan2(-r[1][0], r[0][0]);
		}
		else
		{
			x = std::atan2(r[2][1], r[1][1]);
			z = 0.0f;
		}

		mesh->transform.rotation = glm::degrees(glm::vec3(x, y, z));
	}
}

bool Engine::Gizmo::IsInteracting() const
{
	return interacting;
}

void Engine::Gizmo::Keybinds()
{
	ImGuiIO& io = ImGui::GetIO();
	if (io.WantTextInput || ImGui::IsMouseDown(ImGuiMouseButton_Right) || ImGuizmo::IsUsing())
	{
		return;
	}

	if (ImGui::IsKeyPressed(ImGuiKey_Q, false)) 
	{
		mode = Mode::NONE;
	}
	if (ImGui::IsKeyPressed(ImGuiKey_W, false))
	{
		mode = Mode::TRANSLATE;
	}
	if (ImGui::IsKeyPressed(ImGuiKey_E, false))
	{
		mode = Mode::ROTATE;
	}
	if (ImGui::IsKeyPressed(ImGuiKey_R, false))
	{
		mode = Mode::SCALE;
	}
	if (ImGui::IsKeyPressed(ImGuiKey_T, false))
	{
		mode = Mode::TRANSFORM;
	}
	if (ImGui::IsKeyPressed(ImGuiKey_Y, false))
	{
		space = space == Space::GLOBAL ? Space::LOCAL : Space::GLOBAL;
	}
}
