#include "Liatris.h"

#include "imgui/imgui.h"

#include "Panels/SceneHierarchyPanel.h"

namespace Liatris
{
	
	class EditorLayer : public Layer
	{
	public:
		EditorLayer();

		virtual void OnAttach() override;

		void OnUpdate(Timestep ts) override;

		virtual void OnImGuiRender() override;

		void OnEvent(Event& event) override;

		bool OnKeyPressed(KeyPressedEvent& e);
		bool OnMouseButtonPressed(MouseButtonPressedEvent& e);
	
	private:
		Ref<Framebuffer> m_Framebuffer;
		glm::vec2 m_SceneViewSize = { 0., 0. };
		
		Ref<Scene> m_ActiveScene;

		EditorCamera m_Camera;
		
		bool m_ViewportFocused = false;
		bool m_ViewportHovered = false;

		glm::vec2 m_ViewportBounds[2];
		
		int m_GizmoType = -1;

		float m_Fps = 0.;
		float m_Frames = 0.;
		float m_Timer = 0.;
		Entity m_HoveredEntity;

		SceneHierarchyPanel m_SceneHierarchyPanel;
	};

}
