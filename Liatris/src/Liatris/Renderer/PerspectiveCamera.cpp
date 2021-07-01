#include "liapch.h"
#include "Liatris/Renderer/PerspectiveCamera.h"

#include "glm/gtc/matrix_transform.hpp"

namespace Liatris
{
	PerspectiveCamera::PerspectiveCamera(float fov, float aspect, float n, float f)
		: m_ProjectionMatrix(glm::perspective(fov, aspect, n, f))
		, m_ViewMatrix(1.)
		, m_Position(0.)
	{
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
		m_Fov = fov;
		m_Aspect = aspect;
		m_Near = n;
		m_Far = f;
	}

	void PerspectiveCamera::RecalculateViewMatrix()
	{
		glm::mat4 transform = glm::translate(glm::mat4(1.), m_Position) *
							  glm::rotate   (glm::mat4(1.), m_RightAngle, glm::vec3(0., 1., 0.)) *
							  glm::rotate   (glm::mat4(1.), m_UpAngle   , glm::vec3(1., 0., 0.));

		m_ViewMatrix = glm::inverse(transform);
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}

	void PerspectiveCamera::RecalculateProjectionMatrix()
	{
		m_ProjectionMatrix = glm::perspective(m_Fov, m_Aspect, m_Near, m_Far);
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}
}
