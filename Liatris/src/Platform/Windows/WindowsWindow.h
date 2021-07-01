#pragma once

#include "Liatris/Core/Window.h"
#include "Liatris/Renderer/GraphicsContext.h"

#include <GLFW/glfw3.h>


namespace Liatris {
	class WindowsWindow : public Window
	{
	public:
		WindowsWindow(const WindowProps& props);
		virtual ~WindowsWindow();

		void OnUpdate() override;
		
		virtual unsigned int GetWidth() const override { return m_Data.Width; }

		virtual unsigned int GetHeight() const override { return m_Data.Height; }

		virtual void SetEventCallback(const EventCallbackFn& callback) override { m_Data.EventCallback = callback; }

		virtual void SetVSync(bool enabled) override;

		virtual bool IsVSync() const override;

		inline void* GetNativeWindow() const override { return m_Window; };
		
		virtual void LockMouse(bool lock) override;

	private:
		virtual void Init(const WindowProps& props);
		virtual void Shutdown();
	private:
		GLFWwindow* m_Window;
		GraphicsContext* m_Context;

		struct WindowData
		{
			std::string Title;
			unsigned int Width, Height;
			bool vSync;

			EventCallbackFn EventCallback;
		};

		WindowData m_Data;
	};
}

