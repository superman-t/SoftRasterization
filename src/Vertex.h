#ifndef Vertex_h
#define Vertex_h
#include <vector>

namespace SoftRender {
	struct Vertex{
		Vec3f modelPos;
		Vec3f normal;
		Vec2f uv;
		Color color;
		float derivZ ;
		Vertex():modelPos(Vec3f()),normal(Vec3f()), uv(Vec2f()), color(Color()){}
	};

	struct VertexOut{
		Vec3f worldPos;
		Vec3f viewPos;
		Vec3f projPos;
		Vec3f normal;
		Vec2f uv;
		Color color;
		float derivZ ;
		VertexOut():projPos(Vec3f()),normal(Vec3f()), uv(Vec2f()), color(Color()){}
	};
	
}

#endif
