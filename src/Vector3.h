//
//  Vector3.h
//  Sgraphic
//
//  Created by AceTian on 2017/8/1.
//

#ifndef Vector3_h
#define Vector3_h
#include <cstdlib>
#include <iostream>
#include <cmath>

namespace SoftRender{
	template<typename T>
	class Vec3 {
	public:
		T x, y, z;
	public:
		Vec3():x(T(0)), y(T(0)), z(T(0)){}
		explicit Vec3(T _x, T _y, T _z):x(_x),y(_y),z(_z){}
		explicit Vec3(T xx):x(xx), y(xx), z(xx){}
		Vec3(const Vec3& v) {x = v.x, y = v.y, z = v.z;}

		Vec3<T>& operator=(const Vec3<T>& v){x = v.x; y = v.y;z = v.z; return *this;}

		Vec3<T> operator+(const Vec3<T>& v) const{return Vec3<T>(x + v.x, y + v.y, z + v.z);}
		Vec3<T> operator-(const Vec3<T>& v) const{return Vec3<T>(x - v.x, y - v.y, z - v.z);}
		Vec3<T> operator*(const Vec3<T>& v) const{return Vec3<T>(x * v.x, y * v.y, z * v.z);}
		Vec3<T> operator*(T v) const{return Vec3<T>(x * v, y * v, z * v);}
		Vec3<T> operator/(const Vec3<T>& v) const{return Vec3(x / v.x, y / v.y, z / v.z);}
		Vec3<T> operator/(T v) const{return Vec3<T>(x / v, y / v, z / v);}
		Vec3<T>&operator/= (const T v) { x /= v; y /= v; z /= v; return *this; }
		Vec3<T>&operator*= (const Vec3<T>&v) {x*=v.x , y*=v.y, z*=v.z; return *this;}
		Vec3<T> operator-() const{return Vec3<T>(-x, -y, -z);}
		T operator[](int i) {
			switch (i)
			{
			case 0: return x;
			case 1: return y;
			case 2: return z;
			default:return 0;
			}
		}

		bool operator==(const Vec3<T>& rhs) const
		{
			return (x==rhs.x && y == rhs.y && z == rhs.z);
		}
		bool operator!=(const Vec3<T>& rhs) const
		{
			return !operator==(rhs);
		}
		Vec3<T> Cross(const Vec3<T>& rhs)const{return Vec3<T>(y*rhs.z-z*rhs.y, z*rhs.x - x*rhs.z, x*rhs.y -y*rhs.x);}
		T Dot(const Vec3<T>& rhs) const{ return x*rhs.x + y*rhs.y + z*rhs.z;}
		T LengthSqr() const {return x*x + y*y + z*z;}
		T Length() const
		{
			T len = LengthSqr();
			if (len < 0) return 0;
			return sqrt(len);
		}

		Vec3<T>& Normalize()
		{
			T len = Length();
			if (len > 0)
			{
				T len2 = 1/len;
				x*=len2, y*=len2, z*=len2;
			}
			return *this;
		}

		friend std::ostream& operator << (std::ostream& os, const Vec3<T>& v)
		{
			os << "[" << v.x << " " << v.y << " " << v.z  << "]" << std::endl;
			return os;
		}
	};
	typedef Vec3<float> Vec3f;
}
#endif /* Vector3_h */
