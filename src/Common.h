//
//  Common.h
//  Sgraphic
//
//  Created by AceTian on 2017/8/1.
//
//

#ifndef Common_h
#define Common_h


#include "Sgmath.hpp"
#include "Vector4.h"
#include <vector>

namespace SoftRender
{
	typedef Vec4<float> Vec4f;
	typedef SgMatrix4<float> Mat4f;

    Mat4f Perspective(float radians, float ratio, float near, float far);

	void SaveBmp(std::vector<Vec4f> &frameBuffer, int width, int height, std::string file);
		
	Mat4f ModelMatrix(Vec4f & translate);

	Mat4f ViewMatrix(const Vec4f& look, const Vec4f& at, const Vec4f& up);
	Vec4f TransformPoint(const Vec4f& d, const Mat4f& m);
	Vec4f TransformDir(const Vec4f& d, const Mat4f& m);
	void SaveBmp(std::vector<Vec4f> &frameBuffer, int width, int height, std::string file);
    struct Vertex{
        Vec4f pos, uv, normal, viewPos, color;
    };
    
    struct Index{
        int pos[3], uv[3], normal[3];
    };
    
    struct Texture{
        int width, height;
        float smax, tmax;
		std::vector<Vec4f> data;
    };

	struct Material{
		float ka, kd, ks;
		Texture texture;
	};

	struct Light {
		Vec4f pos, viewPos, ambientColor, diffuseColor, specularColor;
	};

};

#endif /* Common_h */
