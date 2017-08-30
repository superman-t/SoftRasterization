#ifndef Material_h
#define Material_h

namespace SoftRender {
	struct Material{

		Color ambient;//�ڻ���������������巴�����ʲô��ɫ��ͨ�����Ǻ�������ɫ��ͬ����ɫ
		Color diffuse;//��������������������ɫ�����ͻ�������һ����
		Color specular;//������ն��������ɫӰ��
		float shininess;//����ȣ�����߹��ɢ��/�뾶

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