#include "liapch.h"
#include "Liatris/Renderer/RenderCommand.h"

#if defined(LIA_PLATFORM_WINDOWS)
#include "Platform/OpenGL/OpenGLRendererAPI.h"
#endif

namespace Liatris {

#if defined(LIA_PLATFORM_WINDOWS)
	Scope<RendererAPI> RenderCommand::s_RendererAPI = RendererAPI::Create();
#endif

}
