#pragma once
#include <map>

#include "Liatris/Renderer/Shader.h"

#include <glm/fwd.hpp>

typedef unsigned int  GLenum;

namespace Liatris {

	class OpenGLShader : public Shader
	{
	public:
		OpenGLShader(const std::string& path);
		OpenGLShader(const std::string& vertexSrc, const std::string& fragmentSrc);
		~OpenGLShader();

		virtual void Bind() const override;
		virtual void UnBind() const override;
		
	private:
		std::string ReadFile(const std::string& path);
		std::unordered_map<GLenum, std::string> PreProcess(const std::string& source);
		void Compile(const std::unordered_map<GLenum, std::string>& shaderSources);
	private:
		uint32_t m_RendererID;
		std::map<std::string, uint32_t> m_UniformLocations;
		uint32_t GetUniform(std::string name);
	};

	
}
