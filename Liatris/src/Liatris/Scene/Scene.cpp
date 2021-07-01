#include "liapch.h"
#include "Liatris/Scene/Scene.h"

#include <glm/ext/matrix_clip_space.hpp>


#include "Liatris/Scene/Entity.h"
#include "Liatris/Scene/Components.h"

#include "Liatris/Renderer/Renderer.h"

namespace Liatris
{
	Scene::Scene()
	{

	}

	Scene::~Scene()
	{
	}

	Entity Scene::CreateEntity(const std::string& name)
	{
		Entity entity{ m_Registry.create(), this };
		entity.AddComponent<TransformComponent>(glm::vec3(0.));
		auto& tag = entity.AddComponent<TagComponent>(name);
		tag.Tag = name.empty() ? "Entity" : name;
		
		return entity;
	}

	void Scene::DestroyEntity(Entity entity)
	{
		m_Registry.destroy(entity);
	}

	void Scene::OnUpdateEditor(Timestep ts, EditorCamera& camera)
	{
		Renderer::BeginScene(camera, Renderer::GridShader);
		Renderer::EndScene();
		Renderer::BeginScene(camera, Renderer::ColorShader);
		{
			auto view = m_Registry.view<TransformComponent, QuadRendererComponent>();
			for (auto entity : view)
			{
				auto& [transform, mesh] = view.get<TransformComponent, QuadRendererComponent>(entity);
				Renderer::DrawQuad(transform.GetTransform(), mesh.Color, (int)entity);
			}
		}

		{
			auto view = m_Registry.view<TransformComponent, MeshRendererComponent>();
			for (auto entity : view)
			{
				auto& [transform, mesh] = view.get<TransformComponent, MeshRendererComponent>(entity);
				Renderer::DrawModel(transform.GetTransform(), mesh.meshName, (int)entity);
			}
		}

		Renderer::BeginScene(camera, Renderer::CameraFrustumShader);
		{
			auto view = m_Registry.view<TransformComponent, CameraComponent>();
			for (auto entity : view)
			{
				auto& [transform, camera] = view.get<TransformComponent, CameraComponent>(entity);
				Renderer::DrawCameraFrustum(transform.GetTransform(), camera.Camera.GetProjection());
			}
		}
		Renderer::EndScene();
	}

	void Scene::OnUpdateRuntime(Timestep ts)
	{

		{
			m_Registry.view<NativeScriptComponent>().each([=](auto entity, NativeScriptComponent& nsc)
			{
				if(!nsc.Instance)
				{
					nsc.Instance = nsc.InstantiateScript();
					nsc.Instance->m_Entity = { entity, this };
					nsc.Instance->OnCreate();
				}
				
				nsc.Instance->OnUpdate(ts);
			});
		}
		
		Camera* mainCamera = nullptr;
		glm::mat4 cameraTransform;
		{
			auto group = m_Registry.group<TransformComponent, CameraComponent>();
			for (auto entity : group)
			{
				auto& [transform, camera] = group.get<TransformComponent, CameraComponent>(entity);
				if (camera.Main)
				{
					mainCamera = &camera.Camera;
					cameraTransform = transform.GetTransform();
					break;
				}
			}
		}

		if(mainCamera)
		{
			Renderer::BeginScene(*mainCamera, cameraTransform);
			auto view = m_Registry.view<TransformComponent, QuadRendererComponent>();
			for (auto entity : view)
			{
				auto& [transform, mesh] = view.get<TransformComponent, QuadRendererComponent>(entity);
				Renderer::DrawQuad(transform.GetTransform(), mesh.Color);
			}
			Renderer::EndScene();
		}
		
	}

	void Scene::OnViewportResize(uint32_t width, uint32_t height)
	{
		m_ViewportWidth = width;
		m_ViewportHeight = height;
		{
			auto group = m_Registry.view<CameraComponent>();
			for (auto entity : group)
			{
				auto& cameraComponent = group.get<CameraComponent>(entity);
				if (!cameraComponent.FixedAspectRatio)
				{
					cameraComponent.Camera.SetViewportSize(width, height);
				}
			}
		}
	}

	Entity Scene::GetMainCameraEntity()
	{
		auto view = m_Registry.view<CameraComponent>();
		for(auto entity : view)
		{
			const auto& camera = view.get<CameraComponent>(entity);
			if(camera.Main)
			{
				return Entity{ entity, this };
			}
		}
		return {};
	}


	template<typename T>
	void Scene::OnComponentAdded(Entity entity, T& component)
	{
		static_assert(false);
	}

	template<>
	void Scene::OnComponentAdded<TransformComponent>(Entity entity, TransformComponent& component)
	{
	}

	template<>
	void Scene::OnComponentAdded<TagComponent>(Entity entity, TagComponent& component)
	{
	}

	template<>
	void Scene::OnComponentAdded<QuadRendererComponent>(Entity entity, QuadRendererComponent& component)
	{
	}

	template<>
	void Scene::OnComponentAdded<CameraComponent>(Entity entity, CameraComponent& component)
	{
		component.Camera.SetViewportSize(m_ViewportWidth, m_ViewportHeight);
	}

	template<>
	void Scene::OnComponentAdded<NativeScriptComponent>(Entity entity, NativeScriptComponent& component)
	{
	}
	
	template<>
	void Scene::OnComponentAdded<MeshRendererComponent>(Entity entity, MeshRendererComponent& component)
	{
	}
}
