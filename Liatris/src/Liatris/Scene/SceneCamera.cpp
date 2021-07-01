#include "liapch.h"
#include "SceneCamera.h"

#include <glm/ext/matrix_clip_space.hpp>

namespace Liatris
{
	SceneCamera::SceneCamera()
	{
		RecalculateProjection();
	}

	void SceneCamera::SetPerspective(float fov, float nearClip, float farClip)
	{
		m_ProjectionType = ProjectionType::Perspective;
		SetPerspectiveFov(fov);
		SetPerspectiveNearClip(nearClip);
		SetPerspectiveFarClip(farClip);
		RecalculateProjection();
	}

	void SceneCamera::SetOrthographic(float size, float nearClip, float farClip)
	{
		m_ProjectionType = ProjectionType::Orthographic;
		SetOrthographicSize(size);
		SetOrthographicNearClip(nearClip);
		SetOrthographicFarClip(farClip);
		RecalculateProjection();
	}

	void SceneCamera::SetViewportSize(uint32_t width, uint32_t height)
	{
		m_AspectRatio = (float)width / (float)height;
		RecalculateProjection();
	}

	void SceneCamera::RecalculateProjection()
	{
		switch (m_ProjectionType)
		{
		case ProjectionType::Perspective:
			m_Projection = glm::perspective(m_PerspectiveFov, m_AspectRatio, m_PerspectiveNear, m_PerspectiveFar);
			break;
		case ProjectionType::Orthographic:
			float left = -m_OrthographicSize * m_AspectRatio * 0.5f;
			float right = m_OrthographicSize * m_AspectRatio * 0.5f;
			float bottom = -m_OrthographicSize * 0.5;
			float top = m_OrthographicSize * 0.5;
			m_Projection = glm::ortho(left, right, bottom, top, m_OrthographicNear, m_OrthographicFar);
			break;
		}
	}
}
