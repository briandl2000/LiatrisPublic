#include "liapch.h"
#include "Model.h"

#include "Renderer.h"

#if defined(LIA_PLATFORM_WINDOWS)
#include "Platform/OpenGL/OpenGLModel.h"
#endif

namespace Liatris
{
	Ref<Model> Model::Create(std::string path)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None: LIA_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
#if defined(LIA_PLATFORM_WINDOWS)
		case RendererAPI::API::OpenGL: return CreateRef<OpenGLModel>(path);
#endif
		}
		return nullptr;
	}
}
