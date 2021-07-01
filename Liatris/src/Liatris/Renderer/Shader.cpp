#include "liapch.h"
#include "Liatris/Renderer/Shader.h"

#include "Renderer.h"
#include "RendererAPI.h"

#if defined(LIA_PLATFORM_WINDOWS)
#include "Platform/OpenGL/OpenGLShader.h"
#endif

namespace Liatris
{
	Ref<Shader> Shader::Create(const std::string& path)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None: LIA_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
#if defined(LIA_PLATFORM_WINDOWS)
		case RendererAPI::API::OpenGL: return CreateRef<OpenGLShader>(path);
#endif
		}
		return nullptr;
	}
	
	Ref<Shader> Shader::Create(const std::string& vertexSrc, const std::string& fragmentSrc)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None: LIA_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
#if defined(LIA_PLATFORM_WINDOWS)
		case RendererAPI::API::OpenGL: return CreateRef<OpenGLShader>(vertexSrc, fragmentSrc);
#endif
		}
		return nullptr;
	}
}
