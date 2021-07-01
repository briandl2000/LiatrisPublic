#pragma once

#include <glm/trigonometric.hpp>

#include "Liatris/Renderer/Camera.h"

namespace Liatris
{
	class SceneCamera final : public Camera
	{
	public:
		enum class ProjectionType { Perspective = 0, Orthographic = 1};
	public:
		SceneCamera();
		virtual ~SceneCamera() {};

		void SetPerspective(float fov, float nearClip, float farClip);
		
		void SetOrthographic(float size, float nearClip, float farClip);

		void SetViewportSize(uint32_t width, uint32_t height);

		// Perspective
		float GetPerspectiveFov() const { return m_PerspectiveFov; }
		void  SetPerspectiveFov(float fov) { m_PerspectiveFov = glm::radians(glm::clamp(fov, 0.f, 180.f)); RecalculateProjection(); }
		float GetPerspectiveNearClip() const { return m_PerspectiveNear; }
		void  SetPerspectiveNearClip(float nearClip) { m_PerspectiveNear = glm::clamp(nearClip,  0.01f, m_PerspectiveFar); RecalculateProjection();}
		float GetPerspectiveFarClip() const { return m_PerspectiveFar; }
		void  SetPerspectiveFarClip(float farClip) { m_PerspectiveFar = glm::clamp(farClip, m_PerspectiveNear, INFINITY); RecalculateProjection(); }

		// Ortho
		float GetOrthographicSize() const { return m_OrthographicSize; }
		void  SetOrthographicSize(float size) { m_OrthographicSize = glm::clamp(size, 0.f, INFINITY); RecalculateProjection(); }
		float GetOrthographicNearClip() const { return m_OrthographicNear; }
		void  SetOrthographicNearClip(float nearClip) { m_OrthographicNear = glm::clamp(nearClip, m_OrthographicFar, INFINITY); RecalculateProjection(); }
		float GetOrthographicFarClip() const { return m_OrthographicFar; }
		void  SetOrthographicFarClip(float farClip) { m_OrthographicFar = glm::clamp(farClip, -INFINITY, m_OrthographicNear); RecalculateProjection(); }

		// ProjectionType
		ProjectionType GetProjectionType() { return m_ProjectionType; }
		void SetProjectionType(ProjectionType type) { m_ProjectionType = type; RecalculateProjection();}
	
	private:
		void RecalculateProjection();
	private:
		ProjectionType m_ProjectionType = ProjectionType::Perspective;

		// Perspective
		float m_PerspectiveFov = glm::radians(45.f);
		float m_PerspectiveNear = 0.01f;
		float m_PerspectiveFar = 1000.f;

		// Ortho
		float m_OrthographicSize = 10.f;
		float m_OrthographicNear = 5.0f;
		float m_OrthographicFar = -5.f;
		
		float m_AspectRatio = 16.0f/9.0f;
	};
}