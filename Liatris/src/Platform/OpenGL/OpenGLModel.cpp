#include "liapch.h"
#include "OpenGLModel.h"

#define TINYGLTF_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#define TINYGLTF_NO_STB_IMAGE_WRITE
#include "tiny_gltf.h"
#include "glad/glad.h"

namespace Liatris
{
	OpenGLModel::OpenGLModel(std::string path)
	{

		auto mod = new tinygltf::Model();
		tinygltf::TinyGLTF loader;
		std::string err;
		std::string warn;
		bool ret = loader.LoadASCIIFromFile(mod, &err, path);
		//bool ret = loader.LoadBinaryFromFile(&model, &err, &warn, argv[1]); // for binary glTF(.glb)

		if (!warn.empty()) {
			printf("Warn: %s\n", warn.c_str());
		}

		if (!err.empty()) {
			printf("Err: %s\n", err.c_str());
		}

		if (!ret) {
			printf("Failed to parse glTF\n");
		}

		std::vector<uint32_t> VBOs;

		for (const auto& bufferView : mod->bufferViews)
		{
			auto buffer = mod->buffers[bufferView.buffer];


			uint32_t VBO;
			glGenBuffers(1, &VBO);
			glBindBuffer(GL_ARRAY_BUFFER, VBO);

			glBufferData(GL_ARRAY_BUFFER, bufferView.byteLength, &buffer.data[(bufferView.byteOffset)], GL_STATIC_DRAW);
			VBOs.push_back(VBO);
		}

		std::vector<uint32_t> VAOs;
		std::vector<uint32_t> EBOs;

		std::map<std::string, int> attributes = {
			{"POSITION", 0},
			{"TEXCOORD_0", 1},
			{"NORMAL", 2},
			{"TANGENT", 3},
			{"COLOR_0", 4}
		};
		
		for(const auto& mesh : mod->meshes)
		{
			
			for (const auto& primitive : mesh.primitives)
			{
				uint32_t numIndices;
				uint32_t VAO;
				glGenVertexArrays(1, &VAO);

				glBindVertexArray(VAO);

				for (const auto& val : primitive.attributes)
				{
					if (attributes.find(val.first) != attributes.end())
					{
						const auto& accessor = mod->accessors[val.second];
						auto bufferView = mod->bufferViews[accessor.bufferView];
						auto VBO = VBOs[accessor.bufferView];
						glBindBuffer(GL_ARRAY_BUFFER, VBO);

						glEnableVertexAttribArray(attributes[val.first]);
						glVertexAttribPointer(attributes[val.first], accessor.type, accessor.componentType, accessor.normalized, bufferView.byteStride, (void*)(accessor.byteOffset));
					}
				}
				{
					uint32_t EBO;
					auto accessor = mod->accessors[primitive.indices];
					auto bufferView = mod->bufferViews[accessor.bufferView];
					auto buffer = mod->buffers[bufferView.buffer];

					numIndices = static_cast<int>(accessor.count);
					glGenBuffers(1, &EBO);
					glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
					glBufferData(GL_ELEMENT_ARRAY_BUFFER, bufferView.byteLength, &buffer.data[(bufferView.byteOffset) + accessor.byteOffset], GL_STATIC_DRAW);
					EBOs.push_back(EBO);
				}
				VAOs.push_back(VAO);
				meshes.push_back({ VAO, numIndices });
				glBindVertexArray(0);
			}
		}
		
		delete mod;
		mod = nullptr;
		
	}

	OpenGLModel::~OpenGLModel()
	{
	}

	void OpenGLModel::Render()
	{
		for(const auto& mesh : meshes)
		{
			glBindVertexArray(mesh.VAO);
			glDrawElements(GL_TRIANGLES, mesh.NumIndices, GL_UNSIGNED_INT, nullptr);
		}
	}
}
