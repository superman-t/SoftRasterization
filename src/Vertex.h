#ifndef Vertex_h
#define Vertex_h
#include <vector>

namespace SoftRender {
	struct Vertex{
		Vec3f pos;
		Vec3f viewPos;
		Vec3f normal;
		Vec2f uv;
		Color color;
		float derivZ ;
		Vertex():pos(Vec3f()),normal(Vec3f()), uv(Vec2f()), color(Color()){}
	};

	
}

#endif
