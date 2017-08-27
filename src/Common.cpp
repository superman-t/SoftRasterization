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
#include "TextureManager.h"


namespace SoftRender
{
    enum TextureType
    {
        PNG, JPG, BMP
    };
    

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

    /*bool LoadTexture (Texture &texture, std::string file) {
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
    }*/

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

    Mat4f ModelMatrix(Vec3f & translate)
    {
        Mat4f m;

        m[3][0] = translate.x;
        m[3][1] = translate.y;
        m[3][2] = translate.z;
        return m;
    }


    Mat4f ViewMatrix(const Vec3f& look, const Vec3f& at, const Vec3f& up)
    {
        Vec3f zaxis = (look - at).Normalize();
        Vec3f xaxis = up.Cross(zaxis).Normalize();
        Vec3f yaxis = zaxis.Cross(xaxis);
        Vec3f w(look.x, look.y, look.z);//pos in world space
        Mat4f m(xaxis, yaxis, zaxis, w);
        return m.Inverse();//world space to view space's matrix = (camera in world space's pos)'s inverse
    }

    Vec3f operator*(const Vec3f& d, const Mat4f& m )
    {
        Vec3f v;
        float w = d.x*m[0][3] + d.y*m[1][3] + d.z*m[2][3] + m[3][3];
        v.x = (d.x*m[0][0] + d.y*m[1][0] + d.z*m[2][0] + m[3][0])/w;
        v.y = (d.x*m[0][1] + d.y*m[1][1] + d.z*m[2][1] + m[3][1])/w;
        v.z = (d.x*m[0][2] + d.y*m[1][2] + d.z*m[2][2] + m[3][2])/w;
        return v;
    }

	Color operator*(const Color& c, const Vec3f& m )
	{
		Color v;
		v.R = c.R * m.x;
		v.G = c.G * m.y;
		v.B = c.B * m.z;
		v.A = c.A;
		return v;
	}

    Vec4f operator*(const Vec4f& d, const Mat4f& m )
    {
        Vec4f v;
        float w = d.x*m[0][3] + d.y*m[1][3] + d.z*m[2][3] + m[3][3];
        v.x = (d.x*m[0][0] + d.y*m[1][0] + d.z*m[2][0] + m[3][0])/w;
        v.y = (d.x*m[0][1] + d.y*m[1][1] + d.z*m[2][1] + m[3][1])/w;
        v.z = (d.x*m[0][2] + d.y*m[1][2] + d.z*m[2][2] + m[3][2])/w;
        v.w = w;
        return v;
    }

    

    bool Clip(VertexOut& v)
    {
        //opengl cvv,x[-1,1], y[-1,1],z[-1,1]
        if (v.projPos.x >= -1 && v.projPos.x <= 1
            &&v.projPos.y >= -1 && v.projPos.y <= 1
            &&v.projPos.z >= -1 && v.projPos.z <= 1)
            return false;
        return true;
    }

    void Ndc2Screen (Vec3f &pos, float width, float height) {
        pos.x = (pos.x + 1)* 0.5f * width; 
        pos.y = (1 - pos.y)* 0.5f * height;//flip y on screen coordinate

    }

    bool BackFaceCulling (const Vec3f &p0, const Vec3f &p1, const Vec3f &p2) { 
        return (p0.Dot ((p1 - p0).Cross (p2 - p0)) > 0); 
    }
    

    Color NearestFilter(Texture& texture, int s, int t)
    {
        s = s % texture.width;
        t = t % texture.height;
        s = std::max (0, std::min (s, texture.width-1));
        t = std::max (0, std::min (t, texture.height-1));
        /*vector<Color> data = TextureManager::getInstance()->getTexture(texture.path);*/
        
        return TextureManager::getInstance()->textureMaps[texture.path][s + t*texture.width];
    }

    Color BilinearFilter(Texture& texture, float s, float t)
    {
        float sTemp = s + 0.5f, finalS = floor(sTemp), weightS = sTemp - finalS;
        float tTemp = t + 0.5f, finalT = floor(tTemp), weightT = tTemp - finalT;

        return NearestFilter(texture, finalS, finalT)*weightS*weightT + 
            NearestFilter(texture, finalS-1.0f, finalT)*(1.0f-weightS)*weightT +
            NearestFilter(texture, finalS, finalT-1.0f)*weightS*(1.0-weightT) +
            NearestFilter(texture, finalS-1.0f, finalT-1.0f)*(1.0-weightS)*(1.0-weightT);
    }

    Color TextureMap(Texture& texture, Vec2f& uv)
    {
        float u = uv.x, v = uv.y;
        float s = u*(texture.width-1);
        float t = v*(texture.height-1);

        return NearestFilter(texture, s, t);
    }


	void VertexShader(Mat4f& mv, Mat4f& p, Vertex& inVertex, VertexOut& outVertex)
    {
        Mat4f mvp = mv*p;
		Mat4f nmv = mv.Inverse().Transpose();
        Vec4f v = Vec4f(inVertex.modelPos, 1.0f)*(mvp);
        outVertex.projPos.x = v.x;
        outVertex.projPos.y = v.y;
        outVertex.projPos.z = v.z;

        outVertex.derivZ = 1.0f/v.w;

        outVertex.uv = inVertex.uv*outVertex.derivZ;
        outVertex.color = inVertex.color*outVertex.derivZ;
		//Todo: fix worldPos
		outVertex.worldPos = inVertex.modelPos;
        outVertex.viewPos = inVertex.modelPos*mv;

		outVertex.normal = inVertex.normal;
    }

    Color PixelShader(VertexOut& inVertex, Texture& texture, Light& light)
    {
		float ambientStrength = 0.1;
		Color ambient = light.color*ambientStrength;
		ambient.A = 1.0;
		Vec3f norm = inVertex.normal.Normalize();
		Vec3f lightDir = (light.worldPos - inVertex.worldPos).Normalize();
		//std::cout << lightDir ;
		float diff = std::max(norm.Dot(lightDir), 0.0f);
		Color diffuse = light.color*diff;
		diffuse.A = 1.0;
		
		Color result = ambient + diffuse;
// 		std::cout << result.R << 
// 			" "<< result.G << " " <<result.B << std::endl;
        return TextureMap(texture, inVertex.uv)*result;
    }

	Color PixelShader(VertexOut& inVertex, Color& color, Light& light)
	{
		float ambientStrength = 0.1;
		Color ambient = light.color*ambientStrength;
		ambient.A = 1.0;
		Vec3f norm = inVertex.normal.Normalize();
		//std::cout << norm;
		Vec3f lightDir = (light.worldPos - inVertex.worldPos).Normalize();
		float diff = std::max(lightDir.Dot(norm), 0.0f);
		Color diffuse = light.color*diff;
		diffuse.A = 1.0;

		Color result = ambient + diffuse;
		 		
		return color*result;
	}
}