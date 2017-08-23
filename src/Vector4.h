//
//  Vector4.h
//  Sgraphic
//
//  Created by AceTian on 2017/8/1.
//

#ifndef Vector4_h
#define Vector4_h
#include <cstdlib>
#include <iostream>
#include <cmath>
#include "Vector3.h"

namespace SoftRender{
    template<typename T>
	class Vec4 {
    public:
		T x, y, z, w;
	public:
		Vec4():x(T(0)), y(T(0)), z(T(0)),w(T(0)){}
		explicit Vec4(T _x, T _y, T _z, T _w):x(_x),y(_y),z(_z),w(_w){}
		explicit Vec4(T _x, T _y, T _z):x(_x), y(_y), z(_z), w(0.0){}
        explicit Vec4(T xx):x(xx), y(xx), z(xx), w(xx){}
		Vec4(Vec3<T>&v):x(v.x), y(v.y), z(v.z), w(0.0){}
		Vec4(Vec3<T>&v, T _w):x(v.x), y(v.y), z(v.z), w(_w){}
		Vec4(const Vec4& v) {x = v.x, y = v.y, z = v.z, w = v.w;}
    
		Vec4<T>& operator=(const Vec4<T>& v){x = v.x; y = v.y;z = v.z;w = v.w; return *this;}
		Vec4<T>& operator=(const Vec3<T>& v){x = v.x; y = v.y;z = v.z;w = 1.0; return *this;}
    
		Vec4<T> operator+(const Vec4<T>& v) const{return Vec4<T>(x + v.x, y + v.y, z + v.z, w + v.w);}
		Vec4<T> operator-(const Vec4<T>& v) const{return Vec4<T>(x - v.x, y - v.y, z - v.z, w - v.w);}
		Vec4<T> operator*(const Vec4<T>& v) const{return Vec4<T>(x * v.x, y * v.y, z * v.z, w * v.w);}
		Vec4<T> operator*(T v) const{return Vec4<T>(x * v, y * v, z * v, w * v);}
		Vec4<T> operator/(const Vec4<T>& v) const{return Vec4(x / v.x, y / v.y, z / v.z, w / v.w);}
		Vec4<T> operator/(T v) const{return Vec4<T>(x / v, y / v, z / v, w / v);}
		Vec4<T>&operator/= (const T v) { x /= v; y /= v; z /= v; w /= v; return *this; }
        Vec4<T>&operator*= (const Vec4<T>&v) {x*=v.x , y*=v.y, z*=v.z, w*=v.w; return *this;}
		Vec4<T> operator-() const{return Vec4<T>(-x, -y, -z, -w);}
		T operator[](int i) {
			switch (i)
			{
			case 0: return x;
			case 1: return y;
			case 2: return z;
			case 3: return w;
			default:return 0;
			}
		}

		bool operator==(const Vec4<T>& rhs) const
		{
			return (x==rhs.x && y == rhs.y && z == rhs.z && w == rhs.w);
		}
		bool operator!=(const Vec4<T>& rhs) const
		{
			return !operator==(rhs);
		}
		Vec4<T> Cross(const Vec4<T>& rhs)const{return Vec4<T>(y*rhs.z-z*rhs.y, z*rhs.x - x*rhs.z, x*rhs.y -y*rhs.x, 0);}
		T Dot(const Vec4<T>& rhs) const{ return x*rhs.x + y*rhs.y + z*rhs.z + w*rhs.w;}
		T LengthSqr() const {return x*x + y*y + z*z + w*w;}
		T Length() const
		{
			T len = LengthSqr();
			if (len < 0) return 0;
			return sqrt(len);
		}
    
		Vec4<T>& Normalize()
		{
			T len = Length();
            if (len > 0)
            {
                T len2 = 1/len;
                x*=len2, y*=len2, z*=len2;
            }
			return *this;
		}
        
        friend std::ostream& operator << (std::ostream& os, const Vec4<T>& v)
        {
            os << "[" << v.x << " " << v.y << " " << v.z << " " << v.w << "]" << std::endl;
            return os;
        }
	};
    typedef Vec4<float> Vec4f;
}
#endif /* Vector4_h */
