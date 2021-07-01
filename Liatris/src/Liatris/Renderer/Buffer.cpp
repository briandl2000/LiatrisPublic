#include "liapch.h"
#include "Liatris/Renderer/Buffer.h"

#include "Renderer.h"

#if defined(LIA_PLATFORM_WINDOWS)
#include "Platform/OpenGL/OpenGLBuffer.h"
#endif

namespace Liatris {

	Ref<VertexBuffer> VertexBuffer::Create(float* vertices, uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None: LIA_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
#if defined(LIA_PLATFORM_WINDOWS)
		case RendererAPI::API::OpenGL: return CreateRef<OpenGLVertexBuffer>(vertices, size);
#endif
		}
		return nullptr;
	}

	Ref<IndexBuffer> IndexBuffer::Create(uint32_t* indices, uint32_t count)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None: LIA_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
#if defined(LIA_PLATFORM_WINDOWS)
		case RendererAPI::API::OpenGL: return CreateRef<OpenGLIndexBuffer>(indices, count);
#endif
		}
		return nullptr;
	}
}
