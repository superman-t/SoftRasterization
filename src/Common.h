//
//  Sgmath.hpp
//  Sgraphic
//
//  Created by AceTian on 2017/8/1.
//
//

#ifndef Common_h
#define Common_h


#include "Sgmath.hpp"
#include "Vector4.h"
#include <cmath>

namespace SoftRender
{
        // projection Matrix4
		static Mat4f Perspective(float radians, float ratio, float near, float far)
		{
			float r = near * tan(radians*0.5), l = -r, t = r/ratio, b = -t;
			Mat4f p;
			p[0][0] = 2*near/(r-l);
			p[0][2] = (r+l)/(r-l);
			p[1][1] = 2*near/(t-b);
			p[1][2] = (t+b)/(t-b);
			p[2][2] = (near+far)/(near-far);
			p[2][3] = 2*far*near/(near-far);
			p[3][2] = -1.0;
			// above is opengl projection matrix, but hero use row major matrix, so transpose
			return p.Transpose();
		}

		static Mat4f ModelMatrix(Vec4f & translate)
		{
			Mat4f m;
			m[3][0] = translate.x;
			m[3][1] = translate.y;
			m[3][2] = translate.z;
			return m;
		}


		static Mat4f ViewMatrix(const Vec4f& look, const Vec4f& at, const Vec4f& up)
		{
			Vec4f zaxis = (look - at).Normalize();
			Vec4f xaxis = up.Cross(zaxis).Normalize();
			Vec4f yaxis = zaxis.Cross(xaxis);
			Vec4f w(look.x, look.y, look.z, 1);//pos in world space
			Mat4f m(xaxis, yaxis, zaxis, w);
			return m.Inverse();//world space to view space's matrix = (camera in world space's pos)'s inverse
		}

	
		//we use colom major matrix, so dot*M*V*P, in opengl use P*V*M*dot
		static Vec4f TransformDot(const Vec4f& d, const Mat4f& m)
		{
			Vec4f v;
			//float w = d.x*m[0][3] + d.y*m[1][3] + d.z*m[2][3] + d.w*m[3][3];//d.w = 1, because is point
			v.x = (d.x*m[0][0] + d.y*m[1][0] + d.z*m[2][0] + d.w*m[3][0]);
			v.y = (d.x*m[0][1] + d.y*m[1][1] + d.z*m[2][1] + d.w*m[3][1]);
			v.z = (d.x*m[0][2] + d.y*m[1][2] + d.z*m[2][2] + d.w*m[3][2]);
			v.w = d.x*m[0][3] + d.y*m[1][3] + d.z*m[2][3] + d.w*m[3][3];;
			return v;
		}
	
		static Vec4f TransformDir(const Vec4f& d, const Mat4f& m)
		{
			Vec4f v;
			v.x = d.x*m[0][0] + d.y*m[1][0] + d.z*m[2][0];
			v.y = d.x*m[1][0] + d.y*m[1][1] + d.z*m[1][2];
			v.z = d.x*m[2][0] + d.y*m[2][2] + d.z*m[2][2];
			return v;
		}
		
    struct Vertex{
        Vec4f pos, uv, normal, viewPos, color;
    };
    
    struct Index{
        int pos[3], uv[3], normal[3];
    };
    
    struct Texture{
        int width, height;
        //float
    };

};

#endif /* Common_h */
