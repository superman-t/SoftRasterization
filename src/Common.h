#include "Sgmath.hpp"
#include "Vector4.h"
#include <math.h>

namespace Sr
{
	struct Sgm
	{
		// projection Matrix4
		static SgMatrix4 Perspective(float radians, float ratio, float near, float far)
		{
			float r = near * tan(radians*0.5), l = -r, t = r/ratio, b = -t;
			SgMatrix4 p;
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

		static SgMatrix4 ModelMatrix(Vector4 & translate)
		{
			SgMatrix4 m;
			m[3][0] = translate.x;
			m[3][1] = translate.y;
			m[3][2] = translate.z;
			return m;
		}


		static SgMatrix4 ViewMatrix(const Vector4& look, const Vector4& at, const Vector4& up)
		{
			Vector4 zaxis = (look - at).Normalize();
			Vector4 xaxis = up.Cross(zaxis).Normalize();
			Vector4 yaxis = zaxis.Cross(xaxis);
			Vector4 w = Vector4(look.x, look.y, look.z, 1);//pos in world space
			SgMatrix4 m(xaxis, yaxis, zaxis, w);
			return m.Inverse();//world space to view space's matrix = (camera in world space's pos)'s inverse
		}

	
		//we use colom major matrix, so dot*M*V*P, in opengl use P*V*M*dot
		static Vector4 TransformDot(const Vector4& d, const SgMatrix4& m)
		{
			Vector4 v;
			//float w = d.x*m[0][3] + d.y*m[1][3] + d.z*m[2][3] + d.w*m[3][3];//d.w = 1, because is point
			v.x = (d.x*m[0][0] + d.y*m[1][0] + d.z*m[2][0] + d.w*m[3][0]);
			v.y = (d.x*m[0][1] + d.y*m[1][1] + d.z*m[2][1] + d.w*m[3][1]);
			v.z = (d.x*m[0][2] + d.y*m[1][2] + d.z*m[2][2] + d.w*m[3][2]);
			v.w = d.x*m[0][3] + d.y*m[1][3] + d.z*m[2][3] + d.w*m[3][3];;
			return v;
		}
	/*
		static Vector4 TransformDir(const Vector4& d, const SgMatrix4& m)
		{
			Vector4 v;
			v.x = d.x*m[0][0] + d.y*m[1][0] + d.z*m[2][0];
			v.y = d.x*m[1][0] + d.y*m[1][1] + d.z*m[1][2];
			v.z = d.x*m[2][0] + d.y*m[2][2] + d.z*m[2][2];
			return v;
		}
		static Vector4 operator*(const Vector4&d, const SgMatrix4& m)
		{

		}
		*/
 

	};

	Vector4 operator*(Vector4&d, SgMatrix4& m)
	{
		Vector4 v;
		v.x = (d.x*m[0][0] + d.y*m[1][0] + d.z*m[2][0] + d.w*m[3][0]);
		v.y = (d.x*m[0][1] + d.y*m[1][1] + d.z*m[2][1] + d.w*m[3][1]);
		v.z = (d.x*m[0][2] + d.y*m[1][2] + d.z*m[2][2] + d.w*m[3][2]);
		v.w = d.x*m[0][3] + d.y*m[1][3] + d.z*m[2][3] + d.w*m[3][3];;
		return v;
	}

	ostream& operator << (ostream &os, const Vector4 &v)
	{
		os << "Vector4[" << v.x << " " << v.y << " " << v.z << " " << v.w << "]" << std::endl;
		return os;
	}

};