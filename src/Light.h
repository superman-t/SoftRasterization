#ifndef Light_h
#define Light_h

namespace SoftRender {
	struct Light {
		Vec3f position;
		Vec3f ambient;
		Vec3f diffuse;
		Vec3f specular;

		Light():position(Vec3f(1.0, 1.0, 1.0)), ambient(Vec3f(1.0, 1.0, 1.0)), diffuse(Vec3f(1.0, 1.0, 1.0)), specular(Vec3f(1.0, 1.0, 1.0)){}
		Light(Vec3f& _pos, Vec3f& _ambient, Vec3f& _diffuse, Vec3f& _specular):position(_pos),
			ambient(_ambient), diffuse(_diffuse), specular(_specular){}
	};
}
#endif