#ifndef Light_h
#define Light_h

namespace SoftRender {
	struct Light {
		Vec3f worldPos;
		Vec3f viewPos;

		Color ambient;
		Color diffuse;
		Color specular;
		

		Light():worldPos(Vec3f(1.0, 1.0, 1.0)), ambient(Color()), diffuse(Color()), specular(Color()){}
		Light(Vec3f& _pos, Color& _ambient, Color& _diffuse, Color& _specular):worldPos(_pos),
			ambient(_ambient), diffuse(_diffuse), specular(_specular){}
		Light(Light& _light)
		{
			worldPos = _light.worldPos;
			ambient = _light.ambient;
			diffuse = _light.diffuse;
			specular = _light.specular;
		}
	};
}
#endif