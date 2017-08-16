#ifndef Mesh_h
#define Mesh_h
#include <memory>

namespace SoftRender{
	struct Mesh
	{
		std::vector<Vertex> vertices;
		std::vector<unsigned int> indices;
		std::shared_ptr<Texture> texture;

		Mesh( std::vector<Vertex> _vertices,  std::vector<unsigned int> _indices)
		{
			vertices = _vertices;
			indices = _indices;
		}
		Mesh(std::vector<Vertex> _vertices, std::vector<unsigned int> _indices, std::shared_ptr<Texture> _texture)
		{
			vertices = _vertices;
			indices = _indices;
			texture = _texture;
		}

		Mesh(Mesh& _m)
		{
			vertices = _m.vertices;
			indices = _m.indices;
			texture = _m.texture;
		}

	};
}
#endif