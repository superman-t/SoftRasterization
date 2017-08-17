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
	using namespace std;
	Mat4f ModelMatrix(Vec4f & translate);
	Mat4f ViewMatrix(const Vec4f& look, const Vec4f& at, const Vec4f& up);
	Mat4f Perspective(float radians, float ratio, float near, float far);

	Vec4f operator*(const Vec4f& d, const Mat4f& m );
	Vec4f TransformPoint(const Vec4f& d, const Mat4f& m);
	Vec4f TransformDir(const Vec4f& d, const Mat4f& m);

	void SaveTexture(std::vector<Color> &frameBuffer, int width, int height, std::string file);
	bool LoadTexture (Texture &texture, std::string file);

};

#endif /* Common_h */
