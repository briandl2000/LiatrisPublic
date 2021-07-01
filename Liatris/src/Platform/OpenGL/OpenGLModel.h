#pragma once

#include "Liatris/Renderer/Model.h"

namespace Liatris
{
	struct mesh
	{
		uint32_t VAO;
		uint32_t NumIndices;
	};
	class OpenGLModel : public Model
	{
	public:
		OpenGLModel(std::string path);
		virtual ~OpenGLModel() override;

		virtual void Render() override;

	private:
		std::vector<mesh> meshes;
	};
}
