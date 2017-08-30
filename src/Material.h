#ifndef Material_h
#define Material_h

namespace SoftRender {
	struct Material{

		Color ambient;//在环境光照下这个物体反射得是什么颜色，通常这是和物体颜色相同的颜色
		Color diffuse;//在漫反射光照下物体的颜色。（和环境光照一样）
		Color specular;//镜面光照对物体的颜色影响
		float shininess;//反光度，镜面高光的散射/半径

		std::vector<Texture> ambientTextures;
		std::vector<Texture> diffuseTextures;
		std::vector<Texture> specularTextures;

		Material(Color& _ambient, Color& _diffuse, Color& _specular, float _shininess):
			ambient(_ambient), diffuse(_diffuse), specular(_specular), shininess(_shininess){}

		Material():ambient(Color(1.0, 1.0, 1.0)), diffuse(Color(1.0, 1.0, 1.0)), specular(Color(1.0, 1.0, 1.0)), shininess(32.0f){}
		
		Material(Material& _m)
		{
			ambient = _m.ambient;
			diffuse = _m.diffuse;
			specular = _m.specular;
			shininess = _m.shininess;
			ambientTextures = _m.ambientTextures;
			diffuseTextures = _m.diffuseTextures;
			specularTextures = _m.specularTextures;
		}
	};
}

#endif