#include "Render.h"

namespace SoftRender{

	//计算三角形面积
	static inline float calculateArea (const Vec3f &p0, const Vec3f &p1, const Vec3f &p2) {
		return ((p2.x - p0.x) * (p1.y - p0.y) - (p2.y - p0.y) * (p1.x - p0.x));
	} // note that the result of edge function could be represent as area as well.

	static inline bool zTest(float z, float zbuff)
	{
		return z < zbuff;
	}
	//重心法插值uv坐标
	static inline void Interpolate (const Vertex &v0, const Vertex &v1, const Vertex &v2, Vertex &v, Vec3f &w) {
		float area = calculateArea (v0.pos, v1.pos, v2.pos);
		w.x = calculateArea (v1.pos, v2.pos, v.pos) / area; 
		w.y = calculateArea (v2.pos, v0.pos, v.pos) / area;
		w.z = calculateArea (v0.pos, v1.pos, v.pos) / area;
		v.derivZ = v0.derivZ*w.x + v1.derivZ*w.y + v2.derivZ*w.z;
		v.pos.z = 1/v.derivZ;// 1/v.derivZ=观察空间的Z坐标
		v.uv = (v0.uv * w.x + v1.uv * w.y + v2.uv * w.z)/v.derivZ;
		v.color = (v0.color*w.x + v1.color*w.y + v2.color*w.z)/v.derivZ;
	} 
	
	void Render::SetPixel (int x, int y, const Color &color, float depth = 0) {
		if (x >= 0 && x < width && y >= 0 && y < height) {
			frameBuffer[x + y * width] = color;
			depthBuffer[x+y*width] = depth;
		}
	} 

	void Render::DrawLine (const Vec3f &p0, const Vec3f &p1, const Color &color) {
		int x0 = (int)std::floor (p0.x), x1 = (int)std::floor (p1.x), y0 = (int)std::floor (p0.y), y1 = (int)std::floor (p1.y);
		if(x0 > x1) { std::swap(x0, x1); std::swap(y0, y1); }

		int dx = x1 - x0;
		int dy = y1 - y0;
		int delta = dy - dx;
		int f = 0;

		//斜率
		if(dy >= 0 && dy <= dx) {
			for(int x = x0, y = y0; x <= x1; x++) {
				SetPixel(x, y, color);

				if((f + dy) + (f + delta) < 0)
					f += dy;
				else { f += delta; y++; }
			}
		} else if(dy >= 0 && dy > dx) {
			for(int x = x0, y = y0; y <= y1; y++) {
				SetPixel (x, y, color);

				if((f - dx) + (f - dx + dy) > 0)
					f += -dx;
				else { f += -dx + dy; x++; }
			}
		} else if(dy <= 0 && -dy <= dx) {
			for(int x = x0, y = y0; x <= x1; x++) {
				SetPixel (x, y, color);

				if((f + dy) + (f + dy + dx) > 0)
					f += dy;
				else { f += dy + dx; y--; }
			}
		} else if(dy <= 0 && -dy > dx) {
			for(int x = x0, y = y0; y >= y1; y--) {
				SetPixel (x, y, color);

				if((f + dx) + (f + dy + dx) < 0)
					f += dx;
				else { f += dy + dx; x++; }
			}
		}         
	} // bresenham line algorithm

	void Render::DrawTriangle (const Vertex &v0, const Vertex &v1, const Vertex &v2, const Color &color) {
		DrawLine (v0.pos, v1.pos, color); 
		DrawLine (v1.pos, v2.pos, color); 
		DrawLine (v0.pos, v2.pos, color);
	}

	static bool OnSameSide(Vec3f a, Vec3f b, Vec3f c, Vec3f p)
	{
		return (b-a).Cross(c-a).Dot((b-a).Cross(p-a)) >= 0;
	}
	static bool PointInTrangleBySameSide(Vec3f a, Vec3f b, Vec3f c, Vec3f p)
	{
		return OnSameSide(a, b, c, p) &&
			OnSameSide(b, c, a, p)&&
			OnSameSide(c, a, b, p);
	}
	//advanced Rasterization from http://forum.devmaster.net/t/advanced-rasterization/6145/1
/*
	void Render::Rasterization(Mesh& mesh, Vertex& v1, Vertex& v2, Vertex& v3){
		// 28.4 fixed-point coordinates
		const int Y1 = iround(16.0f * v1.pos.y);
		const int Y2 = iround(16.0f * v2.pos.y);
		const int Y3 = iround(16.0f * v3.pos.y);
	
		const int X1 = iround(16.0f * v1.pos.x);
		const int X2 = iround(16.0f * v2.pos.x);
		const int X3 = iround(16.0f * v3.pos.x);
	
		// Deltas
		const int DX12 = X1 - X2;
		const int DX23 = X2 - X3;
		const int DX31 = X3 - X1;
	
		const int DY12 = Y1 - Y2;
		const int DY23 = Y2 - Y3;
		const int DY31 = Y3 - Y1;
	
		// Fixed-point deltas
		const int FDX12 = DX12 << 4;
		const int FDX23 = DX23 << 4;
		const int FDX31 = DX31 << 4;
	
		const int FDY12 = DY12 << 4;
		const int FDY23 = DY23 << 4;
		const int FDY31 = DY31 << 4;
	
		// Bounding rectangle
		int minx = (std::min(std::min(X1, X2), X3) + 0xF) >> 4;
		int maxx = (std::max(std::max(X1, X2), X3) + 0xF) >> 4;
		int miny = (std::min(std::min(Y1, Y2), Y3) + 0xF) >> 4;
		int maxy = (std::max(std::max(Y1, Y2), Y3) + 0xF) >> 4;
	
		// Half-edge constants
		int C1 = DY12 * X1 - DX12 * Y1;
		int C2 = DY23 * X2 - DX23 * Y2;
		int C3 = DY31 * X3 - DX31 * Y3;
	
		// Correct for fill convention
		if(DY12 < 0 || (DY12 == 0 && DX12 > 0)) C1++;
		if(DY23 < 0 || (DY23 == 0 && DX23 > 0)) C2++;
		if(DY31 < 0 || (DY31 == 0 && DX31 > 0)) C3++;
	
		int CY1 = C1 + DX12 * (miny << 4) - DY12 * (minx << 4);
		int CY2 = C2 + DX23 * (miny << 4) - DY23 * (minx << 4);
		int CY3 = C3 + DX31 * (miny << 4) - DY31 * (minx << 4);
		Vec3f weight = Vec3f();
		for(int y = miny; y < maxy; y++)
		{
			int CX1 = CY1;
			int CX2 = CY2;
			int CX3 = CY3;
	
			for(int x = minx; x < maxx; x++)
			{
				if(CX1 >= 0 && CX2 >= 0 && CX3 >= 0)
				{
					Vertex v; v.pos = Vec3f(x+0.5, y+0.5, 0);
					//if (!PointInTrangleBySameSide(v1.pos, v2.pos, v3.pos, v.pos)) continue;
								
		 			Interpolate(v1, v2, v3, v, weight);
		 			if (zTest(v.pos.z, depthBuffer[x+y*width])) 
		 				SetPixel(x, y, mesh.texture->Map(v.uv.x, v.uv.y), v.pos.z);
				}
	
				CX1 -= FDY12;
				CX2 -= FDY23;
				CX3 -= FDY31;
			}
	
			CY1 += FDX12;
			CY2 += FDX23;
			CY3 += FDX31;
		}
	}
*/

	//http://blackpawn.com/texts/pointinpoly/default.html
	static bool PointInTrangleByCentroid(Vec3f a, Vec3f b, Vec3f c, Vec3f p)
	{
		Vec3f v0 = c - a ;
		Vec3f v1 = b - a ;
		Vec3f v2 = p - a ;

		float dot00 = v0.Dot(v0) ;
		float dot01 = v0.Dot(v1) ;
		float dot02 = v0.Dot(v2) ;
		float dot11 = v1.Dot(v1) ;
		float dot12 = v1.Dot(v2) ;

		float inverDeno = 1 / (dot00 * dot11 - dot01 * dot01) ;

		float u = (dot11 * dot02 - dot01 * dot12) * inverDeno ;
		if (u < 0 || u > 1) // if u out of range, return directly
		{
			return false ;
		}

		float v = (dot00 * dot12 - dot01 * dot02) * inverDeno ;
		if (v < 0 || v > 1) // if v out of range, return directly
		{
			return false ;
		}

		return u + v <= 1 ;
	}

	void Render::Rasterization(Mesh& mesh, Vertex& v1, Vertex& v2, Vertex& v3)
	{
		// Bounding rectangle
		int minx = min3(v1.pos.x, v2.pos.x, v3.pos.x);
		int maxx = max3(v1.pos.x, v2.pos.x, v3.pos.x);
		int miny = min3(v1.pos.y, v2.pos.y, v3.pos.y);
		int maxy = max3(v1.pos.y, v2.pos.y, v3.pos.y);

		Vec3f weight = Vec3f();
		for(int y = miny; y <= maxy; y++)
		{
			for(int x = minx; x <= maxx; x++)
			{
				
				Vertex v; v.pos = Vec3f(x+0.5, y+0.5, 0);
				if (!PointInTrangleBySameSide(v1.pos, v2.pos, v3.pos, v.pos)) continue;
				Interpolate(v1, v2, v3, v, weight);
				if (zTest(v.pos.z, depthBuffer[x+y*width])) 
					SetPixel(x, y, PixelShader(v, mesh.textures[0]), v.pos.z);
			}
		}
	}

	void Render::DrawTriangle(Mesh& mesh, Vertex& v0, Vertex& v1, Vertex&v2)
	{
		Vertex outVertex[3];
		VertexShader(mvMat, projMat, v0, outVertex[0]);
		VertexShader(mvMat, projMat, v1, outVertex[1]);
		VertexShader(mvMat, projMat, v2, outVertex[2]);
		for(auto& v : outVertex)
		{
			if (Clip(v)) return;
			Ndc2Screen (v.pos, width, height);
		}

		if (BackFaceCulling (outVertex[0].viewPos,outVertex[1].viewPos,outVertex[2].viewPos)) 
			return;
		if (currentMode == Textured)
		{
			Rasterization(mesh, outVertex[0], outVertex[1], outVertex[2]);
		}else{
			DrawTriangle (outVertex[0], outVertex[1], outVertex[2], Color(0, 1.0f, 0, 0 ));
		}
	}
	void Render::DrawModel (Model &model, bool drawTex = true, bool drawWireFrame = false) {
		mMat = ModelMatrix(model.pos);
		mvMat = mMat * viewMat;
		mvpMat = mvMat * projMat;
		nmvMat = mvMat.Inverse().Transpose ();

		// we need light position(in view space) in pixel shader
		//Vec4f lightViewPos = light.position * mvMat;

		// travers all triangles

		for (auto &mesh : model.meshes) {
			for (int j = 0; j < mesh.indices.size(); j+=3)
			{
				DrawTriangle(mesh, mesh.vertices[j], mesh.vertices[j+1], mesh.vertices[j+2]);
			}
		} 
	}
	
}

