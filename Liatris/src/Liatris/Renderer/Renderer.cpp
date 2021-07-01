#include "liapch.h"
#include "Renderer.h"


#include <map>
#include <glm/ext/matrix_transform.hpp>

#include "Model.h"
#include "UniformBuffer.h"
#include "Shader.h"

namespace Liatris
{

	struct RendererStorage
	{
		Ref<Shader> shader;
		Ref<Shader> gridShader;
		Ref<Shader> cameraFrustumShader;
		
		Ref<VertexArray> quadVertexArray;
		Ref<VertexArray> cubeVertexArray;

		//CameraData
		struct CameraData
		{
			glm::mat4 ViewProjection;
			glm::mat4 View;
			glm::mat4 Projection;
		};
		CameraData CameraBuffer;
		Ref<UniformBuffer> CameraUniformBuffer;

		//ModelData
		struct ModelData
		{
			glm::mat4 Model;
		};
		ModelData ModelBuffer;
		Ref<UniformBuffer> ModelUniformBuffer;

		//FragmentData
		struct FragmentData
		{
			int ID;
		};
		FragmentData FragmentBuffer;
		Ref<UniformBuffer> FragmentUniformBuffer;

		//CameraFrustumData
		struct CameraFrustumData
		{
			glm::mat4 CameraView;
			glm::mat4 CameraProjection;
		};
		CameraFrustumData CameraFrustumBuffer;
		Ref<UniformBuffer> CameraFrustumUniformBuffer;

		std::map<std::string, Ref<Model>> models;
	};

	static RendererStorage s_Data;

	void Renderer::Init()
	{
		s_Data.shader = Shader::Create("assets/shaders/Shader.glsl");
		s_Data.gridShader = Shader::Create("assets/shaders/GridShader.glsl");
		s_Data.cameraFrustumShader = Shader::Create("assets/shaders/CameraFrustumShader.glsl");

		s_Data.quadVertexArray = VertexArray::Create();
		s_Data.cubeVertexArray = VertexArray::Create();

		//quad
		{
			float vertices[] =
			{
				-.5, -.5, 0., 0., 0.,
				 .5, -.5, 0., 1., 0.,
				 .5,  .5, 0., 1., 1.,
				-.5,  .5, 0., 0., 1.,
			};

			Ref<VertexBuffer> vertexBuffer = VertexBuffer::Create(vertices, sizeof(vertices));

			BufferLayout layout = {
				{ ShaderDataType::Float3, "POSITION"  },
				{ ShaderDataType::Float2, "TEXCOORD_0"}
			};

			vertexBuffer->SetLayout(layout);

			uint32_t indices[] =
			{
				0, 1, 2,
				0, 2, 3
			};
			Ref<IndexBuffer> indexBuffer = IndexBuffer::Create(indices, 6);

			s_Data.quadVertexArray->AddVertexBuffer(vertexBuffer);
			s_Data.quadVertexArray->SetIndexBuffer(indexBuffer);
		}

		//cube
		{
			float vertices[] =
			{
				-.5, -.5,  .5,
				 .5, -.5,  .5,
				 .5,  .5,  .5,
				-.5,  .5,  .5,
				
				-.5, -.5, -.5,
				 .5, -.5, -.5,
				 .5,  .5, -.5,
				-.5,  .5, -.5
			};

			Ref<VertexBuffer> vertexBuffer = VertexBuffer::Create(vertices, sizeof(vertices));

			BufferLayout layout = {
				{ ShaderDataType::Float3, "a_Position" }
			};

			vertexBuffer->SetLayout(layout);

			uint32_t indices[] =
			{
				//front
				0, 2, 1,
				0, 3, 2,

				//back
				4, 5, 6,
				4, 6, 7,

				//bottom
				0, 1, 5,
				0, 5, 4,

				//top
				3, 6, 2,
				3, 7, 6,

				//right
				1, 6, 5,
				1, 2, 6,

				//left
				0, 4, 7,
				0, 7, 3
				
			};
			Ref<IndexBuffer> indexBuffer = IndexBuffer::Create(indices, sizeof(indices)/sizeof(uint32_t));

			s_Data.cubeVertexArray->AddVertexBuffer(vertexBuffer);
			s_Data.cubeVertexArray->SetIndexBuffer(indexBuffer);
		}

		s_Data.CameraUniformBuffer = UniformBuffer::Create(sizeof(RendererStorage::CameraData), 0);
		s_Data.ModelUniformBuffer = UniformBuffer::Create(sizeof(RendererStorage::ModelData), 1);
		s_Data.FragmentUniformBuffer = UniformBuffer::Create(sizeof(RendererStorage::FragmentData), 2);
		s_Data.CameraFrustumUniformBuffer = UniformBuffer::Create(sizeof(RendererStorage::CameraFrustumData), 3);

		s_Data.models["assets/Models/CyberBike/scene.gltf"] = Model::Create("assets/Models/CyberBike/scene.gltf");
	}
	
	void Renderer::BeginScene(const Camera& camera, const glm::mat4& transform)
	{
		s_Data.shader->Bind();
		s_Data.CameraBuffer.ViewProjection = camera.GetProjection() * glm::inverse(transform);
		s_Data.CameraUniformBuffer->SetData(&s_Data.CameraBuffer, sizeof(RendererStorage::CameraData));
	}

	void Renderer::BeginScene(const EditorCamera& camera, ShaderID shader)
	{
		s_Data.CameraBuffer.ViewProjection = camera.GetViewProjection();
		s_Data.CameraBuffer.View = camera.GetViewMatrix();
		s_Data.CameraBuffer.Projection = camera.GetProjection();
		s_Data.CameraUniformBuffer->SetData(&s_Data.CameraBuffer, sizeof(RendererStorage::CameraData));
		switch(shader)
		{
			case ShaderID::ColorShader:
				s_Data.shader->Bind();
				break;
			case ShaderID::GridShader:
				s_Data.gridShader->Bind();
				RenderCommand::RenderVertexIndexed(6);
				break;
			case ShaderID::CameraFrustumShader:
				s_Data.cameraFrustumShader->Bind();
				break;

		}
	}

	void Renderer::EndScene()
	{
		s_Data.shader->UnBind();
	}

	void Renderer::DrawQuad(const glm::mat4& model, const glm::vec4& color)
	{
		s_Data.ModelBuffer.Model = model;
		s_Data.ModelUniformBuffer->SetData(&s_Data.ModelBuffer, sizeof(RendererStorage::ModelData));
		RenderCommand::DrawIndexed(s_Data.quadVertexArray);
	}

	void Renderer::DrawCube(const glm::mat4& model, const glm::vec4& color)
	{
		s_Data.ModelBuffer.Model = model;
		s_Data.ModelUniformBuffer->SetData(&s_Data.ModelBuffer, sizeof(RendererStorage::ModelData));
		RenderCommand::DrawIndexed(s_Data.cubeVertexArray);
	}

	void Renderer::DrawModel(const glm::mat4& model, const std::string& name)
	{
		if (s_Data.models.find(name) != s_Data.models.end())
		{
			s_Data.ModelBuffer.Model = model;
			s_Data.ModelUniformBuffer->SetData(&s_Data.ModelBuffer, sizeof(RendererStorage::ModelData));
			s_Data.models[name]->Render();
		}
	}

	void Renderer::DrawQuad(const glm::mat4& model, const glm::vec4& color, int entityID)
	{
		s_Data.ModelBuffer.Model = model;
		s_Data.ModelUniformBuffer->SetData(&s_Data.ModelBuffer, sizeof(RendererStorage::ModelData));
		s_Data.FragmentBuffer.ID = entityID;
		s_Data.FragmentUniformBuffer->SetData(&s_Data.FragmentBuffer, sizeof(RendererStorage::FragmentData));
		RenderCommand::DrawIndexed(s_Data.quadVertexArray);
	}

	void Renderer::DrawCube(const glm::mat4& model, const glm::vec4& color, int entityID)
	{
		s_Data.ModelBuffer.Model = model;
		s_Data.ModelUniformBuffer->SetData(&s_Data.ModelBuffer, sizeof(RendererStorage::ModelData));
		s_Data.FragmentBuffer.ID = entityID;
		s_Data.FragmentUniformBuffer->SetData(&s_Data.FragmentBuffer, sizeof(RendererStorage::FragmentData));
		RenderCommand::DrawIndexed(s_Data.cubeVertexArray);
	}

	void Renderer::DrawModel(const glm::mat4& model, const std::string& name, int entityID)
	{
		if (s_Data.models.find(name) != s_Data.models.end())
		{
			s_Data.ModelBuffer.Model = model;
			s_Data.ModelUniformBuffer->SetData(&s_Data.ModelBuffer, sizeof(RendererStorage::ModelData));
			s_Data.FragmentBuffer.ID = entityID;
			s_Data.FragmentUniformBuffer->SetData(&s_Data.FragmentBuffer, sizeof(RendererStorage::FragmentData));
			s_Data.models[name]->Render();
		}
	}

	void Renderer::DrawCameraFrustum(const glm::mat4& view, const glm::mat4& projection)
	{
		s_Data.CameraFrustumBuffer.CameraView = view;
		s_Data.CameraFrustumBuffer.CameraProjection = projection;
		s_Data.CameraFrustumUniformBuffer->SetData(&s_Data.CameraFrustumBuffer, sizeof(RendererStorage::CameraFrustumData));
		RenderCommand::RenderVertexIndexedLines(8*4);
	}

	void Renderer::Submit(const Ref<VertexArray>& vertexArray)
	{
		RenderCommand::DrawIndexed(vertexArray);
	}
}
 