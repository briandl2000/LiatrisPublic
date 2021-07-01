#include "liapch.h"
#include "Liatris/Renderer/VertexArray.h"

#include "Renderer.h"

#if defined(LIA_PLATFORM_WINDOWS)
#include "Platform/OpenGL/OpenGLVertexArray.h"
#endif

namespace Liatris {
	Ref<VertexArray> VertexArray::Create()
	{
		switch (Renderer::GetAPI())
		{
#if defined(LIA_PLATFORM_WINDOWS)
		case RendererAPI::API::OpenGL: return CreateRef<OpenGLVertexArray>(); break;
#endif
		case RendererAPI::API::None: return nullptr; break;
		}
		return nullptr;
	}
}