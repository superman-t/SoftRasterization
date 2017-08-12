#ifndef Model_h
#define Model_h
#include "Common.h"

namespace SoftRender
{
	struct Model
	{
		std::string path;
		Material material;
		std::vector<Mesh> meshes;
		Texture texture;
		Vec4f pos;

		Model(std::string path, Vec3f& worldPos, Material m);
	private:
		std::string texturename;
		void loadModel(std::string path);
		void setupMesh(std::vector<Vec2f>& uvBuffer, 
			std::vector<Vec4f>& normalBuffer, 
			std::vector<Vec4f>& posBuffer,
			std::vector<Index>& indexBuffer);
	};
}

#endif