#pragma once
#include "Liatris/Renderer/RendererAPI.h"

namespace Liatris {

	class OpenGLRendererAPI : public RendererAPI
	{
	public:
		virtual void ClearColor(const glm::vec4& color) override;
		virtual void Clear() override;

		virtual void DrawIndexed(const Ref<VertexArray>& vertexArray) override;
		virtual void DrawIndexedLines(const Ref<VertexArray>& vertexArray) override;

		virtual void RenderVertexIndexed(uint32_t numVertices) override;
		virtual void RenderVertexIndexedLines(uint32_t numVertices) override;

	private:
	};

}