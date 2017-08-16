#ifndef Model_h
#define Model_h
#include "Common.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

namespace SoftRender
{
	struct Model
	{
		std::string path;
		Material material;
		Texture texture;
		Vec4f pos;
		vector<Mesh> meshes;
		Model(std::string path, Vec3f& worldPos, Material m);
	private:
		string directory;
		std::string texturename;

		void loadModel(string path);
		void processNode(aiNode *node, const aiScene *scene);
		Mesh processMesh(aiMesh *mesh, const aiScene *scene);
		vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, 
			string typeName);
		bool processMaterial(const aiMaterial* matPtr, const aiScene* sceneObjPtr, 
			const aiTextureType textureType, std::vector<Texture>& textures);
	};
}

#endif