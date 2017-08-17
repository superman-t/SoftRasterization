#ifndef Render_h
#define Render_h

#include "Common.h"
#include "Model.h"

namespace SoftRender {
	struct Render
	{
		int width, height;
		std::vector<Color> frameBuffer;
		std::vector<float> depthBuffer;
		Mat4f mMat, projMat, viewMat, mvMat, mvpMat, nmvMat;
		Light light;

		Render (int w, int h) : width (w), height (h), frameBuffer (w * h, Color(0, 0, 0.34f, 0 )), depthBuffer (w * h, 1.0) {	}

		void SetFrustum (float hfov, float ratio, float n, float f) { projMat = Perspective (hfov, ratio, n, f); }

		void SetCamera (Vec3f look, Vec3f at) { viewMat = ViewMatrix (look, at, Vec4f(0.0f, 1.0f, 0.0f, 0.0f )); }

		void SetLight (const Vec3f &pos, const Vec3f &ambi, const Vec3f &diff, const Vec3f &spec) {
			light.position = pos; light.ambient = ambi; light.diffuse = diff;	light.specular = spec;
		} // we support one point light right now.

		void DrawModel (Model &model, bool drawTex, bool drawWireFrame);

		inline void Ndc2Screen (Vec4f &pos) {
			pos.x = (pos.x + 1)* 0.5f * width; 
			pos.y = (1 - pos.y)* 0.5f * height;//flip y on screen coordinate
			
		} // convert from normalized device coordinate to screen coordinate

		//顺时针为背面进行剔除
		inline bool BackFaceCulling (const Vec4f &p0, const Vec4f &p1, const Vec4f &p2) { 
			return (p0.Dot ((p1 - p0).Cross (p2 - p0)) > 0);
		}

		void setPixel (int x, int y, const Color &color);

		void DrawTriangle (const Vertex &v0, const Vertex &v1, const Vertex &v2, const Color &color);
		void DrawLine (const Vec4f &p0, const Vec4f &p1, const Color &color);

		//void FillTriangle (Model &model, const Vertex &v0, const Vertex &v1, const Vertex &v2);
		void FillTriangle(Vertex& v1, Vertex& v2, Vertex& v3, Color color);

		void FillTriangle(Mesh mesh, Vertex& v1, Vertex& v2, Vertex& v3);

		void DrawLineInternal (int x0, int y0, int x1, int y1, const Color &color, bool steep);
	};

}
#endif
