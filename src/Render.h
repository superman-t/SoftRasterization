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
		DrawMode currentMode;

		Render (int w, int h) : width (w), height (h), frameBuffer (w * h, Color(0, 0, 0.34f, 0 )), depthBuffer (w * h, std::numeric_limits<float>::max ()) {	}

		void SetFrustum (float hfov, float ratio, float n, float f) { projMat = Perspective (hfov, ratio, n, f); }

		void SetCamera (Vec3f &look, Vec3f &at) { viewMat = ViewMatrix (look, at, Vec3f(0.0f, 1.0f, 0.0f)); }

		void SetLight (const Vec3f &pos, const Vec3f &ambi, const Vec3f &diff, const Vec3f &spec) {
			light.position = pos; light.ambient = ambi; light.diffuse = diff;	light.specular = spec;
		} // we support one point light right now.

		void DrawModel (Model &model, bool drawTex, bool drawWireFrame);


		void SetPixel (int x, int y, const Color &color, float depth);
		void Rasterization(Mesh&mesh, Vertex& v0, Vertex& v1, Vertex& v2);
		void DrawTriangle (Mesh&mesh, Vertex &v0, Vertex &v1, Vertex &v2);
		void DrawLine (const Vec3f &p0, const Vec3f &p1, const Color &color);

		//void FillTriangle (Model &model, const Vertex &v0, const Vertex &v1, const Vertex &v2);
		void DrawTriangle(const Vertex& v1, const Vertex& v2, const Vertex& v3, const Color& color);

		void FillTriangle(Mesh& mesh, Vertex& v1, Vertex& v2, Vertex& v3);

		void DrawLineInternal (int x0, int y0, int x1, int y1, const Color &color, bool steep);
	};

}
#endif