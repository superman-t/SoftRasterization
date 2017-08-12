#ifndef Light_h
#define Light_h

namespace SoftRender {
	struct Light {
		Vec4f position;
		Vec4f ambient;
		Vec4f diffuse;
		Vec4f specular;

		Light():position(Vec4f(1.0, 1.0, 1.0)), ambient(Vec4f(1.0, 1.0, 1.0)), diffuse(Vec4f(1.0, 1.0, 1.0)), specular(Vec4f(1.0, 1.0, 1.0)){}
		Light(Vec4f& _pos, Vec4f& _ambient, Vec4f& _diffuse, Vec4f& _specular):position(_pos),
			ambient(_ambient), diffuse(_diffuse), specular(_specular){}
	};
}
#endif