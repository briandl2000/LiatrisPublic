#pragma once

#include "Liatris/Core/Window.h"
#include "Liatris/Core/LayerStack.h"
#include "Liatris/Events/Event.h" 
#include "Liatris/Events/ApplicationEvent.h"

#include "Liatris/Core/Timestep.h"

#include "Liatris/ImGui/ImGuiLayer.h"


namespace Liatris {

	class Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

		static void LockMouse(bool lock);
		
		inline static Application& Get() { return *s_Instance; }

		inline Window& GetWindow() { return *m_Window; }

		void Close();

		ImGuiLayer* GetImGuiLayer() { return m_ImGuiLayer; }
	
	private:
		bool OnWindowClose(WindowCloseEvent& e);

	private:
		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		LayerStack m_LayerStack;
		float m_LastFrameTime = 0.0f;
	
	private:
		static Application* s_Instance;
	};

	Application* CreateApplication();
}
