#include "liapch.h"
#include "Platform/OpenGL/OpenGLRendererAPI.h"

#include <glad/glad.h>

namespace Liatris {

	void OpenGLRendererAPI::ClearColor(const glm::vec4& color)
	{
		glClearColor(color.x, color.y, color.z, color.w);
	}

	void OpenGLRendererAPI::Clear()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void OpenGLRendererAPI::DrawIndexed(const Ref<VertexArray>& vertexArray)
	{
		vertexArray->Bind();
		glDrawElements(GL_TRIANGLES, vertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
	}

	void OpenGLRendererAPI::DrawIndexedLines(const Ref<VertexArray>& vertexArray)
	{
		vertexArray->Bind();
		glDrawElements(GL_LINE, vertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
	}

	void OpenGLRendererAPI::RenderVertexIndexed(uint32_t numVertices)
	{
		glDrawArrays(GL_TRIANGLES, 0, numVertices);
	}

	void OpenGLRendererAPI::RenderVertexIndexedLines(uint32_t numVertices)
	{
		glDrawArrays(GL_LINES, 0, numVertices);
	}
}
