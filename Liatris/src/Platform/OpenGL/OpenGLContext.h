#pragma once
#include "Liatris/Renderer/GraphicsContext.h"

struct GLFWwindow;

namespace Liatris {

	class OpenGLContext : public GraphicsContext
	{
	public:
		OpenGLContext(GLFWwindow* windowHandle);

		void Init() override;
		void SwapBuffers() override;
	private:
		GLFWwindow* m_WindowHandle;
	};

}