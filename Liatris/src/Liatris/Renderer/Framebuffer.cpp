#include "liapch.h"
#include "Liatris/Renderer/Framebuffer.h"

#include "Renderer.h"

#if defined(LIA_PLATFORM_WINDOWS)
#include "Platform/OpenGL/OpenGLFramebuffer.h"
#endif

namespace Liatris
{
	Ref<Framebuffer> Framebuffer::Create(const FramebufferSpecification& spec)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None: return nullptr;
#if defined(LIA_PLATFORM_WINDOWS)
		case RendererAPI::API::OpenGL: return CreateRef<OpenGLFramebuffer>(spec);
#endif
		}
	}

}
