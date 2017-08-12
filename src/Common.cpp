//
//  Common.cpp
//  Sgraphic
//
//  Created by AceTian on 2017/8/5.
//
//

#include "Common.h"
#include <ostream>
#include <fstream>


namespace SoftRender
{
	void SaveBmp(std::vector<Color> &frameBuffer, int width, int height, std::string file)
	{
#define INT2CHAR_BIT(num, bit) (unsigned char)(((num) >> (bit)) & 0xff)
#define INT2CHAR(num) INT2CHAR_BIT((num),0), INT2CHAR_BIT((num),8), INT2CHAR_BIT((num),16), INT2CHAR_BIT((num),24)
		unsigned char buf[54] = { 'B', 'M', INT2CHAR (54 + width*height * 32), INT2CHAR (0), INT2CHAR (54), INT2CHAR (40), INT2CHAR (width), INT2CHAR (height), 1, 0, 32, 0 };
		std::ofstream ofs (file, std::ios_base::out | std::ios_base::binary);
		ofs.write ((char *)buf, sizeof (buf));
		for (auto &color : frameBuffer) {
			buf[0] = (unsigned char)std::min (255, (int)(color.B * 255));
			buf[1] = (unsigned char)std::min (255, (int)(color.G * 255));
			buf[2] = (unsigned char)std::min (255, (int)(color.R * 255));
			buf[3] = (unsigned char)std::min (255, (int)(color.A * 255));
			ofs.write ((char *)buf, 4);
		}
	}

	bool LoadBmp (Texture &texture, std::string file) {
		std::ifstream is (file, std::ios_base::binary);
		if (!is) return false;
		unsigned char buf[54];
		is.read ((char *)buf, sizeof (buf));
		// in bmp header, height could be negtive
		texture.width = *(int *)&buf[18], texture.height = abs (*(int *)&buf[22]);
		int bytes = buf[28] / 8, count = texture.width * texture.height * bytes;
		unsigned char *tmp = new unsigned char[count];
		is.read ((char *)tmp, count);
		texture.data.resize (texture.width * texture.height);
		count = 0;
		for (auto &color : texture.data) {
			color = Color(tmp[count + 2] / 255.0f, tmp[count + 1] / 255.0f, tmp[count + 0] / 255.0f, 0.0f );
			count += bytes;
		}
		delete[]tmp;
		return true;
	} // load bmp into texture

	

	// projection Matrix4
	Mat4f Perspective(float radians, float ratio, float near, float far)
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
		p[3][3] = 0.0;
		// above is opengl projection matrix, but hero use row major matrix, so transpose
		return p.Transpose();
	}

	Mat4f ModelMatrix(Vec4f & translate)
	{
		Mat4f m;

		m[3][0] = translate.x;
		m[3][1] = translate.y;
		m[3][2] = translate.z;
		return m;
	}


	Mat4f ViewMatrix(const Vec4f& look, const Vec4f& at, const Vec4f& up)
	{
		Vec4f zaxis = (look - at).Normalize();
		Vec4f xaxis = up.Cross(zaxis).Normalize();
		Vec4f yaxis = zaxis.Cross(xaxis);
		Vec4f w(look.x, look.y, look.z, 1);//pos in world space
		Mat4f m(xaxis, yaxis, zaxis, w);
		return m.Inverse();//world space to view space's matrix = (camera in world space's pos)'s inverse
	}

	Vec4f TransformPoint (const Vec4f &b, const Mat4f &mat) {
		Vec4f v;
		v.w = b.x * mat.m[0][3] + b.y * mat.m[1][3] + b.z * mat.m[2][3] + mat.m[3][3];
		v.x = (b.x * mat.m[0][0] + b.y * mat.m[1][0] + b.z * mat.m[2][0] + mat.m[3][0]) / v.w;
		v.y = (b.x * mat.m[0][1] + b.y * mat.m[1][1] + b.z * mat.m[2][1] + mat.m[3][1]) / v.w;
		v.z = (b.x * mat.m[0][2] + b.y * mat.m[1][2] + b.z * mat.m[2][2] + mat.m[3][2]) / v.w;
		return v;
	} // using matrix to transform a point.

	Vec4f TransformDir(const Vec4f& d, const Mat4f& m)
	{
		Vec4f v;
		v.x = d.x*m[0][0] + d.y*m[1][0] + d.z*m[2][0];
		v.y = d.x*m[1][0] + d.y*m[1][1] + d.z*m[1][2];
		v.z = d.x*m[2][0] + d.y*m[2][2] + d.z*m[2][2];
		return v;
	}

	Vec4f operator*(const Vec4f& d, const Mat4f& m )
	{
		Vec4f v;
		v.w = d.x*m[0][3] + d.y*m[1][3] + d.z*m[2][3] + m[3][3];
		v.x = (d.x*m[0][0] + d.y*m[1][0] + d.z*m[2][0] + m[3][0]);
		v.y = (d.x*m[0][1] + d.y*m[1][1] + d.z*m[2][1] + m[3][1]);
		v.z = (d.x*m[0][2] + d.y*m[1][2] + d.z*m[2][2] + m[3][2]);
		return v;
	}

}