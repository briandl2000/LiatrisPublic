#pragma once
#include "VertexArray.h"
#include "glm/vec4.hpp"

namespace Liatris {

	class RendererAPI
	{
	public:
		enum class API
		{
			None = 0, OpenGL
		};
	public:
		virtual ~RendererAPI() = default;
		virtual void ClearColor(const glm::vec4& color) = 0;
		virtual void Clear() = 0;

		virtual void DrawIndexed(const Ref<VertexArray>& vertexArray) = 0;
		virtual void DrawIndexedLines(const Ref<VertexArray>& vertexArray) = 0;

		virtual void RenderVertexIndexed(uint32_t numVertices) = 0;
		virtual void RenderVertexIndexedLines(uint32_t numVertices) = 0;
		
		inline static API GetAPI() { return s_API; }

		static Scope<RendererAPI> Create();
	private:
		static API s_API;
	};

}