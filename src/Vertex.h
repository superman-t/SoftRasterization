#ifndef Vertex_h
#define Vertex_h
#include <vector>

namespace SoftRender {
	struct Vertex{
		Vec4f pos;
		Vec4f viewPos;
		Vec4f normal;
		Vec2f uv;
		Color color;
		Vertex():pos(Vec4f()),normal(Vec4f()), uv(Vec2f()), color(Color()){}
	};

	
}

#endif
