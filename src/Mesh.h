#ifndef Mesh_h
#define Mesh_h
#include <memory>

namespace SoftRender{
	struct Mesh
	{
		std::vector<Vertex> vertices;
		std::vector<unsigned int> indices;
		std::vector<Texture> textures;

<<<<<<< HEAD
		Mesh( std::vector<Vertex> _vertices,  std::vector<unsigned int> _indices)
		{
			vertices = _vertices;
			indices = _indices;
		}
		Mesh(std::vector<Vertex>& _vertices, std::vector<unsigned int>& _indices, std::vector<Texture>& _textures)
=======
//		Mesh( std::vector<Vertex> _vertices,  std::vector<unsigned int> _indices)
//		{
//			vertices = _vertices;
//			indices = _indices;
//		}
		Mesh(std::vector<Vertex> _vertices, std::vector<unsigned int> _indices, std::shared_ptr<Texture> _texture)
>>>>>>> 11b53dbf1583022b10d8d3c2dad14fbfef220561
		{
			vertices = _vertices;
			indices = _indices;
			textures = _textures;
		}

<<<<<<< HEAD
		Mesh(Mesh& _m)
		{
			vertices = _m.vertices;
			indices = _m.indices;
			textures = _m.textures;
		}
=======
//		Mesh(Mesh& _m)
//		{
//			vertices = _m.vertices;
//			indices = _m.indices;
//			texture = _m.texture;
//		}
>>>>>>> 11b53dbf1583022b10d8d3c2dad14fbfef220561

	};
}
#endif
