#pragma once

#include "Liatris/Renderer/RendererAPI.h"

namespace Liatris {

	class RenderCommand
	{
	public:

		inline static void ClearColor(const glm::vec4& color) { s_RendererAPI->ClearColor(color); };
		inline static void Clear() { s_RendererAPI->Clear(); };

		inline static void DrawIndexed(const Ref<VertexArray>& vertexArray) { s_RendererAPI->DrawIndexed(vertexArray); }
		inline static void DrawIndexedLines(const Ref<VertexArray>& vertexArray) { s_RendererAPI->DrawIndexedLines(vertexArray); }
		
		inline static void RenderVertexIndexed(uint32_t numVertices) { s_RendererAPI->RenderVertexIndexed(numVertices); }
		inline static void RenderVertexIndexedLines(uint32_t numVertices) { s_RendererAPI->RenderVertexIndexedLines(numVertices); }

	private:
		static Scope<RendererAPI>s_RendererAPI;
	};

}