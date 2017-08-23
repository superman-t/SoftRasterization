#ifndef Material_h
#define Material_h

namespace SoftRender {
	struct Material{
		Vec3f ambient;
		Vec3f diffuse;
		Vec3f specular;

		Material(Vec3f& _ambient, Vec3f& _diffuse, Vec3f& _specular):ambient(_ambient), diffuse(_diffuse), specular(_specular){}
		Material():ambient(Vec3f(1.0, 1.0, 1.0)), diffuse(Vec3f(1.0, 1.0, 1.0)), specular(Vec3f(1.0, 1.0, 1.0)){}
	};
}

#endif