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
#include <algorithm>


namespace SoftRender
{
    enum TextureType
    {
        PNG, JPG, BMP
    };
    
    //png, jpg, jpeg, bmp, tga
    void SaveTexture(std::vector<Color> &frameBuffer, int width, int height, std::string& file)
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
        v.w = d.x*m[0][3] + d.y*m[1][3] + d.z*m[2][3] + m[3][3];
        v.x = (d.x*m[0][0] + d.y*m[1][0] + d.z*m[2][0] + m[3][0]);
        v.y = (d.x*m[0][1] + d.y*m[1][1] + d.z*m[2][1] + m[3][1]);
        v.z = (d.x*m[0][2] + d.y*m[1][2] + d.z*m[2][2] + m[3][2]);
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


	void VertexShader(Mat4f& model, Mat4f& view, Mat4f& proj, Vertex& inVertex, VertexOut& outVertex)
    {
        Mat4f mvp = model * view * proj;
		Mat4f nmv = model * view.Inverse().Transpose();
        Vec4f v = Vec4f(inVertex.modelPos, 1.0f)*(mvp);

        outVertex.projPos.x = v.x/v.w;
        outVertex.projPos.y = v.y/v.w;
        outVertex.projPos.z = v.z/v.w;

        outVertex.derivZ = 1.0f/v.w;

        outVertex.uv = inVertex.uv*outVertex.derivZ;
        outVertex.color = inVertex.color*outVertex.derivZ;

		outVertex.worldPos = MultPointMatrix(inVertex.modelPos, model);
        outVertex.viewPos = MultPointMatrix(inVertex.modelPos, model*view);

		outVertex.normal = MultDirMatrix(inVertex.normal, model.Inverse().Transpose());
    }

	Vec3f Reflect(const Vec3f& incident, const Vec3f& normal)
	{
		return incident - normal*(2.0*(normal.Dot(incident)));
	}

    Color PixelShader(VertexOut& inVertex, Texture& texture, Light& light, Vec3f& cameraPos, Material& material)
    {
		Color ambient = light.ambient*material.ambient;

		Vec3f norm = inVertex.normal.Normalize();
		Vec3f lightDir = (light.worldPos - inVertex.worldPos).Normalize();
		float diff = std::max(lightDir.Dot(norm), 0.0f);
		Color diffuse = light.diffuse*(material.diffuse*diff);


		Vec3f viewDir = (cameraPos - inVertex.worldPos).Normalize();
		Vec3f reflectDir = Reflect(-lightDir, norm).Normalize();
		float spec = std::pow(std::max(viewDir.Dot(reflectDir), 0.0f), 128);
		Color specular = light.specular * (material.specular*spec);

		Color result = ambient + diffuse + specular;
		result.A = 1.0;
        return TextureMap(texture, inVertex.uv)*result;
    }

	

	Color PixelShader(VertexOut& inVertex, Mesh& mesh, Light& light, Vec3f& cameraPos)
	{
		Color ambient = light.ambient*TextureMap(mesh.diffuseTextures[0], inVertex.uv);

		Vec3f norm = inVertex.normal.Normalize();
		Vec3f lightDir = (light.worldPos - inVertex.worldPos).Normalize();
		float diff = std::max(lightDir.Dot(norm), 0.0f);
		Color diffuse = light.diffuse*(TextureMap(mesh.diffuseTextures[0], inVertex.uv)*diff);


		Vec3f viewDir = (cameraPos - inVertex.worldPos).Normalize();
		Vec3f reflectDir = Reflect(-lightDir, norm).Normalize();
		float spec = std::pow(std::max(viewDir.Dot(reflectDir), 0.0f), 128);
		Color specular = light.specular * (TextureMap(mesh.specularTextures[0], inVertex.uv)*spec);

		Color result = ambient + diffuse + specular;
		result.A = 1.0;

		return result;
	}

	Color PixelShader(VertexOut& inVertex, Light& light, Vec3f& cameraPos, Material& material)
	{
		Color ambient = light.ambient*material.ambient;

		Vec3f norm = inVertex.normal.Normalize();
		Vec3f lightDir = (light.worldPos - inVertex.worldPos).Normalize();
		float diff = std::max(lightDir.Dot(norm), 0.0f);
		Color diffuse = light.diffuse*(material.diffuse*diff);


		Vec3f viewDir = (cameraPos - inVertex.worldPos).Normalize();
		Vec3f reflectDir = Reflect(-lightDir, norm).Normalize();
		float spec = std::pow(std::max(viewDir.Dot(reflectDir), 0.0f), 128);
		Color specular = light.specular * (material.specular*spec);

		Color result = ambient + diffuse + specular;
		result.A = 1.0;

		return result;
	}
}
