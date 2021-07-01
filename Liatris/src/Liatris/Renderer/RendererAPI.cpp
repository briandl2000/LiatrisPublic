#include "liapch.h"
#include "Liatris/Renderer/RendererAPI.h"

#if defined(LIA_PLATFORM_WINDOWS)
#include "Platform/OpenGL/OpenGLRendererAPI.h"
#endif


namespace Liatris {

	RendererAPI::API RendererAPI::s_API = API::OpenGL;

	Scope<RendererAPI> RendererAPI::Create()
	{
		switch (s_API)
		{
		case RendererAPI::API::None:    LIA_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:  return CreateScope<OpenGLRendererAPI>();
		}

		LIA_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

}
