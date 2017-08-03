//
//  Vector4.h
//  Sgraphic
//
//  Created by AceTian on 2017/8/1.
//  Copyright © 2017年 AceTian. All rights reserved.
//

#ifndef Vector4_h
#define Vector4_h
#include <stdlib.h>
#include <iostream>
#include <algorithm>
#include <math.h>
#include "Sgmath.hpp"

namespace Sr{
	struct Vector4 {
		float x, y, z, w;
		Vector4():x(0), y(0), z(0),w(0){}
		Vector4(float _x, float _y, float _z, float _w):x(_x),y(_y),z(_z),w(_w){}
		Vector4(const Vector4 &v):x(v.x),y(v.y),z(v.z),w(v.w) {}
    
		Vector4& operator=(const Vector4& v){
			x = v.x;
			y = v.y;
			z = v.z;
			w = v.w;
			return *this;
		}
    
		Vector4 operator+(const Vector4& v) const{return Vector4(x + v.x, y + v.y, z + v.z, w + v.w);}
		Vector4 operator-(const Vector4& v) const{return Vector4(x - v.x, y - v.y, z - v.z, w - v.w);}
		Vector4 operator*(const Vector4& v) const{return Vector4(x * v.x, y * v.y, z * v.z, w * v.w);}
		Vector4 operator*(float v) const{return Vector4(x * v, y * v, z * v, w * v);}
		Vector4 operator/(const Vector4& v) const{return Vector4(x / v.x, y / v.y, z / v.z, w / v.w);}
		Vector4 operator/(float v) const{return Vector4(x / v, y / v, z / v, w / v);}
		Vector4&operator/= (const float v) { x /= v; y /= v; z /= v; w /= v; return *this; }
		Vector4 operator-() const{return Vector4(-x, -y, -z, -w);}
		float operator[](int i) {
			switch (i)
			{
			case 1: return x;
			case 2: return y;
			case 3: return z;
			case 4: return w;
			default:return 0;
			}
		}

	

		bool operator==(const Vector4& rhs) const
		{
			return (x==rhs.x && y == rhs.y && z == rhs.z && w == rhs.w);
		}
		bool operator!=(const Vector4& rhs) const
		{
			return !operator==(rhs);
		}
		Vector4 Cross(const Vector4& rhs)const
		{
			return Vector4(y*rhs.z-z*rhs.y, z*rhs.x - x*rhs.z, x*rhs.y -y*rhs.x, 0);
		}
		float Dot(const Vector4& rhs) const
		{
			return x*rhs.x + y*rhs.y + z*rhs.z + w*rhs.w;
		}
    
		float LengthSqr() const {return x*x + y*y + z*z + w*w;}
    
		float Length() const
		{
			float len = LengthSqr();
			if (len < 0) return 0;
			return sqrtf(len);
		}
    
		Vector4& Normalize()
		{
			float len = LengthSqr();
			return *this/=len;
		}
    
	};
}
#endif /* Vector4_h */
