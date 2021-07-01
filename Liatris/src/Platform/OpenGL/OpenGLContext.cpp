#include "liapch.h"
#include "OpenGLContext.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace Liatris {

	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle) 
		: m_WindowHandle(windowHandle)
	{
		LIA_CORE_ASSERT(windowHandle, "Window handle is null!")
	}

	void OpenGLContext::Init()
	{
		glfwMakeContextCurrent(m_WindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		LIA_CORE_ASSERT(status, "Filed to initialize Glad!");

		LIA_CORE_INFO("OpenGL Renderer:");
		LIA_CORE_INFO("  Vendor: {0}", glGetString(GL_VENDOR));
		LIA_CORE_INFO("  Renderer: {0}", glGetString(GL_RENDERER));
		LIA_CORE_INFO("  Version: {0}", glGetString(GL_VERSION));
	}

	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(m_WindowHandle);
	}

}