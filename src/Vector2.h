//
//  Vector2.h
//  Sgraphic
//
//  Created by AceTian on 2017/8/1.
//

#ifndef Vector2_h
#define Vector2_h
#include <cstdlib>
#include <iostream>
#include <cmath>

namespace SoftRender{
	template<typename T>
	class Vec2 {
	public:
		T x, y;
	public:
		Vec2():x(T(0)), y(T(0)){}
		explicit Vec2(T _x, T _y):x(_x),y(_y){}
		explicit Vec2(T xx):x(xx), y(xx){}
		Vec2(const Vec2& v) {x = v.x, y = v.y;}

		Vec2<T>& operator=(const Vec2<T>& v){x = v.x; y = v.y; return *this;}

		Vec2<T> operator+(const Vec2<T>& v) const{return Vec2<T>(x + v.x, y + v.y);}
		Vec2<T> operator-(const Vec2<T>& v) const{return Vec2<T>(x - v.x, y - v.y);}
		Vec2<T> operator*(const Vec2<T>& v) const{return Vec2<T>(x * v.x, y * v.y);}
		Vec2<T> operator*(T v) const{return Vec2<T>(x * v, y * v);}
		Vec2<T> operator/(const Vec2<T>& v) const{return Vec2(x / v.x, y / v.y);}
		Vec2<T> operator/(T v) const{return Vec2<T>(x / v, y / v);}
		Vec2<T>&operator/= (const T v) { x /= v; y /= v; return *this; }
		Vec2<T>&operator*= (const Vec2<T>&v) {x*=v.x , y*=v.y; return *this;}
		Vec2<T> operator-() const{return Vec2<T>(-x, -y);}
		T operator[](int i) {
			switch (i)
			{
			case 0: return x;
			case 1: return y;
			default:return 0;
			}
		}

		bool operator==(const Vec2<T>& rhs) const
		{
			return (x==rhs.x && y == rhs.y);
		}
		bool operator!=(const Vec2<T>& rhs) const
		{
			return !operator==(rhs);
		}
		//Vec2<T> Cross(const Vec2<T>& rhs)const{return Vec2<T>(y*rhs.z-z*rhs.y, z*rhs.x - x*rhs.z, x*rhs.y -y*rhs.x);}
		T Dot(const Vec2<T>& rhs) const{ return x*rhs.x + y*rhs.y;}
		T LengthSqr() const {return x*x + y*y;}
		T Length() const
		{
			T len = LengthSqr();
			if (len < 0) return 0;
			return sqrt(len);
		}

		Vec2<T>& Normalize()
		{
			T len = Length();
			if (len > 0)
			{
				T len2 = 1/len;
				x*=len2, y*=len2;
			}
			return *this;
		}

		friend std::ostream& operator << (std::ostream& os, const Vec2<T>& v)
		{
			os << "[" << v.x << " " << v.y << "]" << std::endl;
			return os;
		}
	};
	typedef Vec2<float> Vec2f;
}
#endif /* Vector2_h */
