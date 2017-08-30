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
		Vec3f pos;
		vector<Mesh> meshes;
		Model(std::string path, Vec3f worldPos, Material m);
        Model(const Model& m)
        {
            path = m.path;
            pos = m.pos;
            material = m.material;
        }
	private:
		string directory;

		void loadModel(string path);
		void processNode(aiNode *node, const aiScene *scene);
		Mesh processMesh(aiMesh *mesh, const aiScene *scene);
		vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, 
			string typeName);
		unsigned int TextureFromFile(Texture& texture, const string& path, const string& directory);
	};
}

#endif
