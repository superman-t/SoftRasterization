#ifndef Mesh_h
#define Mesh_h
#include <memory>

namespace SoftRender{
	struct Mesh
	{
		std::vector<Vertex> vertices;
		std::vector<unsigned short> indices;
		std::shared_ptr<Texture> texture;

		Mesh(std::vector<Vertex> _vertices, std::vector<unsigned short> _indices)
			:vertices(_vertices), indices(_indices) {}
		Mesh(std::vector<Vertex> _vertices, std::vector<unsigned short> _indices, std::shared_ptr<Texture> _texture)
			:vertices(_vertices), indices(_indices), texture(_texture) {}

	};
}
#endif