#pragma once

#include <glm/glm.hpp>
#include <glm/ext/matrix_transform.hpp>

#define  GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>

#include "SceneCamera.h"
#include "ScriptableEntity.h"


namespace Liatris
{

	struct TagComponent
	{
		std::string Tag;

		TagComponent() = default;
		TagComponent(const TagComponent&) = default;
		TagComponent(const std::string& tag)
			: Tag(tag) {}
	};

	struct TransformComponent
	{
		glm::vec3 Translation = { 0., 0., 0. };
		glm::vec3 Rotation = { 0., 0., 0. };
		glm::vec3 Scale = { 1., 1., 1. };

		TransformComponent() = default;
		TransformComponent(const TransformComponent&) = default;
		TransformComponent(const glm::vec3& translation)
			: Translation(translation) {}

		glm::mat4 GetTransform() const
		{
			glm::mat4 rotation = glm::toMat4(glm::quat(Rotation));

			return glm::translate(glm::mat4(1.0f), Translation) *
				rotation *
				glm::scale(glm::mat4(1.), Scale);
		}

	};

	struct QuadRendererComponent
	{
		glm::vec4 Color{ 1. };

		QuadRendererComponent() = default;
		QuadRendererComponent(const QuadRendererComponent&) = default;
		QuadRendererComponent(const glm::vec4& color)
			: Color(color) {}
	};

	struct CameraComponent
	{
		SceneCamera Camera;
		bool Main = true;
		bool FixedAspectRatio = false;

		CameraComponent() = default;
		CameraComponent(const CameraComponent&) = default;
	};

	struct NativeScriptComponent
	{
		ScriptableEntity* Instance = nullptr;

		ScriptableEntity* (*InstantiateScript)();
		void(*DestroyScript)(NativeScriptComponent*);


		template<typename T>
		void Bind()
		{
			InstantiateScript = []() { return static_cast<ScriptableEntity*>(new T()); };
			DestroyScript = [](NativeScriptComponent* nsc) {delete nsc->Instance; nsc->Instance = nullptr; };

		}
	};

	struct MeshRendererComponent
	{
		std::string meshName;
		
		MeshRendererComponent() = default;
		MeshRendererComponent(const MeshRendererComponent&) = default;
	};
	
}
