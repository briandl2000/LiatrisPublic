#pragma once

#include <glm/glm.hpp>
#include <glm/ext/scalar_constants.hpp>

namespace Liatris
{
	class PerspectiveCamera
	{
	public:
		PerspectiveCamera(float fov, float aspect, float n, float f);

		const glm::vec3& GetPosition() const { return m_Position; }
		float GetRotationX() const { return m_UpAngle; }
		float GetRotationY() const { return m_RightAngle; }
		
		void SetPosition(const glm::vec3& position) { m_Position	 = position;	RecalculateViewMatrix();}
		void SetRotateX(float rotation)				{ m_UpAngle		 = rotation;	RecalculateViewMatrix();}
		void SetRotateY(float rotation)				{ m_RightAngle	 = rotation;	RecalculateViewMatrix();}
		void AddRotateX(float rotation)
		{
			m_UpAngle += rotation;
			float clampRotation = glm::pi<float>() * 0.5;
			m_UpAngle = glm::clamp(m_UpAngle, -clampRotation, clampRotation);
			RecalculateViewMatrix();
		}
		void AddRotateY(float rotation)				{ m_RightAngle	+= rotation;	RecalculateViewMatrix();}

		void SetAspectRatio(float aspectRatio) { m_Aspect = aspectRatio; RecalculateProjectionMatrix(); }
		void SetFovRatio(float fov) { m_Fov = fov; RecalculateProjectionMatrix(); }
		
		const glm::mat4& GetProjectionMatrix() const { return m_ProjectionMatrix; }
		const glm::mat4& GetViewMatrix() const { return m_ViewMatrix; }
		const glm::mat4& GetViewProjectionMatrix() const { return m_ViewProjectionMatrix; }
	
	private:
		void RecalculateViewMatrix();
		void RecalculateProjectionMatrix();
	
	private:
		glm::mat4 m_ProjectionMatrix;
		glm::mat4 m_ViewMatrix;
		glm::mat4 m_ViewProjectionMatrix;
		
		glm::vec3 m_Position;
		float m_RightAngle = 0.;
		float m_UpAngle = 0.;
		float m_Fov;
		float m_Aspect = 0.;
		float m_Near = 0.;
		float m_Far = 0.;
	}; 
}
