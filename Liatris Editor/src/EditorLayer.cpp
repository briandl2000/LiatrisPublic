
#include "EditorLayer.h"


#include <glm/ext/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


#include "imgui/imgui.h"
#include "Platform/OpenGL/OpenGLShader.h"

#include "ImGuizmo.h"
#include "Liatris/Math/Math.h"

namespace Liatris
{
		
	EditorLayer::EditorLayer()
		:Layer("EditorLayer")
	{
	}

	void EditorLayer::OnAttach()
	{

		Liatris::FramebufferSpecification fbSpec;
		fbSpec.Attachments = { FramebufferTextureFormat::RGBA8, FramebufferTextureFormat::RED_INTEGER, FramebufferTextureFormat::Depth };
		fbSpec.Width = Application::Get().GetWindow().GetWidth();
		fbSpec.Height = Application::Get().GetWindow().GetHeight();
		m_Framebuffer = Liatris::Framebuffer::Create(fbSpec);

		m_ActiveScene = CreateRef<Scene>();
		m_ActiveScene->OnViewportResize(fbSpec.Width, fbSpec.Height);

		m_SceneHierarchyPanel.SetContext(m_ActiveScene);

		m_Camera = EditorCamera(60.0f, 16.f / 9.f, 0.03f, 10000.f);

		auto& bike = m_ActiveScene->CreateEntity("bike");
		bike.AddComponent<MeshRendererComponent>().meshName = "assets/Models/CyberBike/scene.gltf";
	}

	void EditorLayer::OnUpdate(Liatris::Timestep ts)
	{
		if( FramebufferSpecification spec = m_Framebuffer->GetSpecification();
			m_SceneViewSize.x > 0.0f && m_SceneViewSize.y > 0.0f &&
			(spec.Width != m_SceneViewSize.x || spec.Height != m_SceneViewSize.y))
		{
			m_Framebuffer->Resize(m_SceneViewSize.x, m_SceneViewSize.y);
			m_ActiveScene->OnViewportResize(m_SceneViewSize.x, m_SceneViewSize.y);
			m_Camera.SetViewportSize(m_SceneViewSize.x, m_SceneViewSize.y);
		}
		
		
		if(m_ViewportHovered)
		{
			m_Camera.OnUpdate(ts);
		}

		//Render
		m_Framebuffer->Bind();
		RenderCommand::ClearColor({0.2f, 0.2f, 0.2f, 1.0f});
		RenderCommand::Clear();

		m_Framebuffer->ClearAttachment(1, -1);
		
		m_ActiveScene->OnUpdateEditor(ts, m_Camera);

		auto [mx, my] = ImGui::GetMousePos();
		mx -= m_ViewportBounds[0].x;
		my -= m_ViewportBounds[0].y;
		glm::vec2 viewportSize = m_ViewportBounds[1] - m_ViewportBounds[0];
		my = viewportSize.y - my;
		int mouseX = (int)mx;
		int mouseY = (int)my;

		if(mouseX >= 0 && mouseY >= 0 && mouseX < (int)viewportSize.x && mouseY < (int)viewportSize.y)
		{
			int pixelData = m_Framebuffer->ReadPixel(1, mouseX, mouseY);
			m_HoveredEntity = pixelData == -1 ? Entity() : Entity({(entt::entity)pixelData, m_ActiveScene.get()});
		}
		
		m_Framebuffer->UnBind();


		m_Timer += ts;
		m_Frames++;
		if (m_Timer > 1.)
		{
			m_Fps = m_Frames;
			m_Timer = 0.;
			m_Frames = 0.;
		}
	}

	void EditorLayer::OnImGuiRender()
	{		
		static bool dockSpaceOpen = true;
		static bool opt_fullscreen = true;
		static bool opt_padding = false;
		static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

		// We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
		// because it would be confusing to have two docking targets within each others.
		ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
		if (opt_fullscreen)
		{
			ImGuiViewport* viewport = ImGui::GetMainViewport();
			ImGui::SetNextWindowPos(viewport->GetWorkPos());
			ImGui::SetNextWindowSize(viewport->GetWorkSize());
			ImGui::SetNextWindowViewport(viewport->ID);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
			window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
			window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
		}
		else
		{
			dockspace_flags &= ~ImGuiDockNodeFlags_PassthruCentralNode;
		}

		// When using ImGuiDockNodeFlags_PassthruCentralNode, DockSpace() will render our background
		// and handle the pass-thru hole, so we ask Begin() to not render a background.
		if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
			window_flags |= ImGuiWindowFlags_NoBackground;

		// Important: note that we proceed even if Begin() returns false (aka window is collapsed).
		// This is because we want to keep our DockSpace() active. If a DockSpace() is inactive,
		// all active windows docked into it will lose their parent and become undocked.
		// We cannot preserve the docking relationship between an active window and an inactive docking, otherwise
		// any change of dockspace/settings would lead to windows being stuck in limbo and never being visible.
		if (!opt_padding)
			ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
		ImGui::Begin("DockSpace Demo", &dockSpaceOpen, window_flags);
		if (!opt_padding)
			ImGui::PopStyleVar();

		if (opt_fullscreen)
			ImGui::PopStyleVar(2);

		// DockSpace
		ImGuiStyle& style = ImGui::GetStyle();
		float minWinSize = style.WindowMinSize.x;
		style.WindowMinSize.x = 570.0f;
		ImGuiIO& io = ImGui::GetIO();
		if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
		{
			ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
			ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
		}

		style.WindowMinSize.x = minWinSize;
		
		if (ImGui::BeginMenuBar())
		{
			if (ImGui::BeginMenu("File"))
			{
				if (ImGui::MenuItem("Exit")) { Liatris::Application::Get().Close(); }
				ImGui::Separator();
				ImGui::EndMenu();
			}

			ImGui::EndMenuBar();
		}

		m_SceneHierarchyPanel.OnImGuiRender();

		ImGui::Begin("Stats");

		std::string name = "None";
		//auto stats = Renderer::GetStats();
		std::string hoveredEntityTag = "None";
		if (m_HoveredEntity)
			hoveredEntityTag = m_HoveredEntity.GetComponent<TagComponent>().Tag;
		ImGui::Text("Hovered Entity: %s", hoveredEntityTag.c_str());
		ImGui::Text("Renderer Stats:");
		ImGui::Text("FPS: %f", m_Fps);
		//ImGui::Text("Draw Calls: %d", stats.DrawCalls);

		ImGui::End();
		
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0., 0.));
		ImGui::Begin("Scene view");

		auto viewportMinRegion = ImGui::GetWindowContentRegionMin();
		auto viewportMaxRegion = ImGui::GetWindowContentRegionMax();
		auto viewportOffset = ImGui::GetWindowPos();
		m_ViewportBounds[0] = { viewportMinRegion.x + viewportOffset.x, viewportMinRegion.y + viewportOffset.y };
		m_ViewportBounds[1] = { viewportMaxRegion.x + viewportOffset.x, viewportMaxRegion.y + viewportOffset.y };
		
		m_ViewportFocused = ImGui::IsWindowFocused();
		m_ViewportHovered = ImGui::IsWindowHovered();

		ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();

		Liatris::Application::Get().GetImGuiLayer()->BlockEvents(!m_ViewportFocused && !m_ViewportHovered);
		
		if (m_SceneViewSize != *((glm::vec2*)(&viewportPanelSize)))
		{
			m_SceneViewSize = { viewportPanelSize.x, viewportPanelSize.y };
		}
		uint32_t textureID = m_Framebuffer->GetColorAttachmentRendererID(0);
		ImGui::Image((void*)textureID, viewportPanelSize, ImVec2(0., 1.), ImVec2(1., 0.));

		// Gizmos
		Entity selectedEntity = m_SceneHierarchyPanel.GetSelectedEntity();
		if(selectedEntity && m_GizmoType != -1)
		{
			ImGuizmo::SetOrthographic(false);
			ImGuizmo::SetDrawlist();

			ImVec2 vMin = ImGui::GetWindowContentRegionMin();
			float windowWidth = (float)ImGui::GetWindowWidth()-vMin.x;
			float windowHeight = (float)ImGui::GetWindowHeight()-vMin.y;
			vMin.x += ImGui::GetWindowPos().x;
			vMin.y += ImGui::GetWindowPos().y;
			ImGuizmo::SetRect(vMin.x, vMin.y, windowWidth, windowHeight);

			// Camera
			//auto cameraEntity = m_ActiveScene->GetMainCameraEntity();
			//const auto& camera = cameraEntity.GetComponent<CameraComponent>().Camera;
			//const glm::mat4& cameraProjection = camera.GetProjection();
			//glm::mat4 cameraView = glm::inverse(cameraEntity.GetComponent<TransformComponent>().GetTransform());

			auto& tc = selectedEntity.GetComponent<TransformComponent>();
			glm::mat4 transform = tc.GetTransform();

			bool snap = Input::IsKeyPressed(LIA_KEY_LEFT_CONTROL);
			float snapValue = 0.5f;
			if (m_GizmoType == ImGuizmo::OPERATION::ROTATE)
				snapValue = 45.0f;

			float snapValues[3] = { snapValue, snapValue, snapValue };
			
			ImGuizmo::Manipulate(glm::value_ptr(m_Camera.GetViewMatrix()), glm::value_ptr(m_Camera.GetProjection()),
				(ImGuizmo::OPERATION)m_GizmoType, ImGuizmo::LOCAL, glm::value_ptr(transform), nullptr,
				snap? snapValues : nullptr);

			if(ImGuizmo::IsUsing())
			{
				glm::vec3 translation;
				glm::vec3 rotation;
				glm::vec3 scale;
				Math::DecomposeTransform(transform, translation, rotation, scale);

				glm::vec3 deltaRotation = rotation - tc.Rotation;
				tc.Translation = translation;
				tc.Rotation += deltaRotation;
				tc.Scale = scale;
				
			}
			
		}
		
		bool show = true;
		//ImGui::ShowDemoWindow(&show);

		ImGui::End();
		ImGui::PopStyleVar();

		ImGui::End();
	}

	void EditorLayer::OnEvent(Liatris::Event& event)
	{
		m_Camera.OnEvent(event);
		
		EventDispatcher dispatcher(event);
		dispatcher.Dispatch<KeyPressedEvent>(LIA_BIND_EVENT_FN(EditorLayer::OnKeyPressed));
		dispatcher.Dispatch<MouseButtonPressedEvent>(LIA_BIND_EVENT_FN(EditorLayer::OnMouseButtonPressed));
	}

	bool EditorLayer::OnKeyPressed(KeyPressedEvent& e)
	{
		// Shortcuts
		if (e.GetRepeatCount() > 0)
			return false;

		bool control = Input::IsKeyPressed(LIA_KEY_LEFT_CONTROL) || Input::IsKeyPressed(LIA_KEY_RIGHT_CONTROL);
		bool shift = Input::IsKeyPressed(LIA_KEY_LEFT_SHIFT) || Input::IsKeyPressed(LIA_KEY_RIGHT_SHIFT);

		switch (e.GetKeyCode())
		{
		// Gizmos
		case LIA_KEY_Q:
		{
			if (!ImGuizmo::IsUsing())
				m_GizmoType = -1;
			break;
		}
		case LIA_KEY_W:
		{
			if (!ImGuizmo::IsUsing())
				m_GizmoType = ImGuizmo::OPERATION::TRANSLATE;
			break;
		}
		case LIA_KEY_E:
		{
			if (!ImGuizmo::IsUsing())
				m_GizmoType = ImGuizmo::OPERATION::ROTATE;
			break;
		}
		case LIA_KEY_R:
		{
			if (!ImGuizmo::IsUsing())
				m_GizmoType = ImGuizmo::OPERATION::SCALE;
			break;
		}
		}
	}

	bool EditorLayer::OnMouseButtonPressed(MouseButtonPressedEvent& e)
	{
		if(e.GetMouseButton() == LIA_MOUSE_BUTTON_1)
			if(m_ViewportHovered && !ImGuizmo::IsOver() )
				m_SceneHierarchyPanel.SetSelectedEntity(m_HoveredEntity);
		return true;
	}
}
