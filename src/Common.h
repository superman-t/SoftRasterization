//
//  Common.h
//  Sgraphic
//
//  Created by AceTian on 2017/8/1.
//
//

#ifndef Common_h
#define Common_h

#include <vector>
#include "slm.h"
#include "Color.h"
#include "Vertex.h"
#include "Texture.h"

#include "Light.h"
#include "Material.h"
#include "Mesh.h"


namespace SoftRender
{
	enum DrawMode{
		Textured, WireFrame
	};
	using namespace std;
	Mat4f ModelMatrix(Vec3f & translate);
	Mat4f ViewMatrix(const Vec3f& look, const Vec3f& at, const Vec3f& up);
	Mat4f Perspective(float radians, float ratio, float near, float far);

	Vec3f operator*(const Vec3f& d, const Mat4f& m );
	template<typename T>
	Vec3<T> MultDirMatrix(const Vec3<T>& d, const Matrix4<T>& m)
	{
		Vec3<T> v;
		v.x = (d.x*m[0][0] + d.y*m[1][0] + d.z*m[2][0]);
		v.y = (d.x*m[0][1] + d.y*m[1][1] + d.z*m[2][1]);
		v.z = (d.x*m[0][2] + d.y*m[1][2] + d.z*m[2][2]);
		return v;
	}
	template<typename T>
	Vec3<T> MultPointMatrix(const Vec3<T>& d, const Matrix4<T>& m)
	{
		Vec3<T> v;
		T w = d.x*m[0][3] + d.y*m[1][3] + d.z*m[2][3] + m[3][3];
		v.x = (d.x*m[0][0] + d.y*m[1][0] + d.z*m[2][0] + m[3][0])/w;
		v.y = (d.x*m[0][1] + d.y*m[1][1] + d.z*m[2][1] + m[3][1])/w;
		v.z = (d.x*m[0][2] + d.y*m[1][2] + d.z*m[2][2] + m[3][2])/w;
		return v;
	}

	template<typename T>
	T min3(T a, T b, T c)
	{
		return std::min(a, std::min(b, c));
	}
	template<typename T>
	T max3(T a, T b, T c)
	{
		return std::max(a, std::max(b, c));
	}
	void SaveTexture(std::vector<Color> &frameBuffer, int width, int height, std::string& file);
	bool LoadTexture (Texture &texture, std::string file);

	void VertexShader(Mat4f& model, Mat4f& view, Mat4f& proj, Vertex& inVertex, VertexOut& outVertex);
	bool Clip(VertexOut& v);
	void Ndc2Screen (Vec3f &pos, float width, float height);
	bool BackFaceCulling (const Vec3f &p0, const Vec3f &p1, const Vec3f &p2);
	Color PixelShader(VertexOut& inVertex, Texture& texture, Light& light, Vec3f& cameraPos, Material& material);
	Color PixelShader(VertexOut& inVertex, Mesh& mesh, Light& light, Vec3f& cameraPos);
	Color PixelShader(VertexOut& inVertex, Light& light, Vec3f& cameraPos, Material& material);
	Color BilinearFilter(Texture& texture, float s, float t);
	Color NearestFilter(Texture& texture, int s, int t);
};

#endif /* Common_h */
