#ifndef Mesh_h
#define Mesh_h
#include <memory>

namespace SoftRender{
	struct Mesh
	{
		std::vector<Vertex> vertices;
		std::vector<unsigned int> indices;
		std::vector<Texture> textures;

		Mesh( std::vector<Vertex> _vertices,  std::vector<unsigned int> _indices)
		{
			vertices = _vertices;
			indices = _indices;
		}
		Mesh(std::vector<Vertex>& _vertices, std::vector<unsigned int>& _indices, std::vector<Texture>& _textures)
		{
			vertices = _vertices;
			indices = _indices;
			textures = _textures;
		}

		Mesh(Mesh& _m)
		{
			vertices = _m.vertices;
			indices = _m.indices;
			textures = _m.textures;
		}

	};
}
#endif