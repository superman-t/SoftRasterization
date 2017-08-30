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
		Vec3f cameraPos;
		Light light;
		Material material;
		DrawMode currentMode;

		Render (int w, int h) : width (w), height (h), frameBuffer (w * h, Color(0.1, 0.1, 0.1f, 1 )), depthBuffer (w * h, std::numeric_limits<float>::max ()) {
			currentMode = Textured;
		}

		void SetFrustum (float hfov, float ratio, float n, float f) { projMat = Perspective (hfov, ratio, n, f); }

		void SetCamera (const Vec3f &look) { 
			cameraPos = look;
			viewMat = ViewMatrix (look, Vec3f(), Vec3f(0.0f, 1.0f, 0.0f)); 
		}


		void SetLight (const Light& _light) {
			light = _light;
		}

		void DrawModel (Model &model);


		void SetPixel (int x, int y, const Color &color, float depth);
		void Rasterization(Mesh&mesh, VertexOut& v0, VertexOut& v1, VertexOut& v2);
		void DrawMesh (Mesh&mesh, Vertex &v0, Vertex &v1, Vertex &v2);
		void DrawLine (const Vec3f &p0, const Vec3f &p1, const Color &color);

		//void FillTriangle (Model &model, const Vertex &v0, const Vertex &v1, const Vertex &v2);
		void DrawTriangle(const VertexOut& v1, const VertexOut& v2, const VertexOut& v3, const Color& color);

		void FillTriangle(Mesh& mesh, Vertex& v1, Vertex& v2, Vertex& v3);

		void DrawLineInternal (int x0, int y0, int x1, int y1, const Color &color, bool steep);
	};

}
#endif
