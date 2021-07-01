#include "liapch.h"
#include "Liatris/Renderer/UniformBuffer.h"

#include "Liatris/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLUniformBuffer.h"

namespace Liatris
{
	Ref<UniformBuffer> UniformBuffer::Create(uint32_t size, uint32_t binding)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None: LIA_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
			case RendererAPI::API::OpenGL: return CreateRef<OpenGLUniformBuffer>(size, binding);
		}
		
		LIA_CORE_ASSERT(false, "Unkown RendererAPI");
		return nullptr;
	}

}
