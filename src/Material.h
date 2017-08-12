#ifndef Material_h
#define Material_h

namespace SoftRender {
	struct Material{
		Vec4f ambient;
		Vec4f diffuse;
		Vec4f specular;

		Material(Vec4f& _ambient, Vec4f& _diffuse, Vec4f& _specular):ambient(_ambient), diffuse(_diffuse), specular(_specular){}
		Material():ambient(Vec4f(1.0, 1.0, 1.0)), diffuse(Vec4f(1.0, 1.0, 1.0)), specular(Vec4f(1.0, 1.0, 1.0)){}
	};
}

#endif