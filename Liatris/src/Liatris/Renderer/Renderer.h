#pragma once
#include "RenderCommand.h"

#include "Camera.h"
#include "EditorCamera.h"

namespace Liatris
{

	class Renderer
	{
	public:
		enum ShaderID
		{
			ColorShader = 0, GridShader, CameraFrustumShader, MeshShader
		};
		
		static void Init();
		
		static void BeginScene(const Camera& camera, const glm::mat4& transform);
		static void BeginScene(const EditorCamera& camera, ShaderID shader);
		static void EndScene();

		static void DrawQuad(const glm::mat4& model, const glm::vec4& color);
		static void DrawCube(const glm::mat4& model, const glm::vec4& color);
		static void DrawModel(const glm::mat4& model, const std::string& name);

		static void DrawQuad(const glm::mat4& model, const glm::vec4& color, int entityID);
		static void DrawCube(const glm::mat4& model, const glm::vec4& color, int entityID);
		static void DrawModel(const glm::mat4& model, const std::string& name, int entityID);

		static void DrawCameraFrustum(const glm::mat4& view, const glm::mat4& projection);
		
		static void Submit(const Ref<VertexArray>& vertexArray);
		
		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
	};
	
}
