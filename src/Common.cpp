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
#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image.h"
#include "stb_image_write.h"


namespace SoftRender
{
	enum TextureType
	{
		PNG, JPG, BMP
	};
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

	//png, jpg, jpeg, bmp, tga
	void SaveTexture(std::vector<Color> &frameBuffer, int width, int height, std::string file)
	{
		std::string suffix = file.substr(file.find_last_of('.')+1);
		int comp = 3;
		TextureType type;
		if(!suffix.compare("png"))
		{
			comp = 4;
			type = PNG;
		}else if(!suffix.compare("jpg"))
			type = JPG;	
		else if(!suffix.compare("bmp"))
			type = BMP;

		unsigned char* data = new unsigned char[width*height*comp];
		int count = 0;
		
		for (auto &color : frameBuffer) {
			data[count+0] = (unsigned char)std::min (255, (int)(color.R * 255));
			data[count+1] = (unsigned char)std::min (255, (int)(color.G * 255));
			data[count+2] = (unsigned char)std::min (255, (int)(color.B * 255));
			if (type == PNG) data[count+3] = (unsigned char)std::min (255, (int)(color.A * 255));
			count += comp;
		}

		switch (type)
		{
		case PNG:
			stbi_write_png(file.c_str(), width, height, comp, data, width*4);
			break;
		case JPG:
			stbi_write_jpg(file.c_str(), width, height, comp, data, 100);
			break;
		case BMP:
			stbi_write_bmp(file.c_str(), width, height, comp, data);
			break;
		default:
			std::cout << "save texture failed" << std::endl;
			break;
		}
		delete[] data;
	}

	bool LoadTexture (Texture &texture, std::string file) {
		//     N=#comp     components
		//       1           grey
		//       2           grey, alpha
		//       3           red, green, blue
		//       4           red, green, blue, alpha
		int comp;
		unsigned char* tmp = stbi_load(file.c_str(), &texture.width, &texture.height, &comp, STBI_rgb);
		if (tmp == NULL)
		{
			std::cout << "load file failed" << std::endl;
			return false;
		}

		int count = texture.width * texture.height * STBI_rgb;

		texture.data.resize (texture.width * texture.height);
		count = 0;
		for (auto &color : texture.data) {
			color = Color(tmp[count + 2] / 255.0f, tmp[count + 1] / 255.0f, tmp[count + 0] / 255.0f );
			count += STBI_rgb;
		}
		
		stbi_image_free(tmp);
		return true;
	}

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
