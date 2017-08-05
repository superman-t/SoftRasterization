//
//  Sgmath.hpp
//  Sgraphic
//
//  Created by AceTian on 2017/8/1.
//
//

#ifndef Sgmath_hpp
#define Sgmath_hpp

#include "Vector4.h"
#include <cstdlib>
#include <iostream>
#include <string>

namespace SoftRender{
    template<typename T>
	struct SgMatrix4
	{
		T m[4][4];
		SgMatrix4 (){ memset(m, 0, sizeof(m)); m[0][0] = m[1][1] = m[2][2] = m[3][3] = 1.0; }

		SgMatrix4(Vec4<T>& x, Vec4<T>& y, Vec4<T>& z);
		SgMatrix4(Vec4<T>& x, Vec4<T>& y, Vec4<T>& z, Vec4<T>& w);

		SgMatrix4(const SgMatrix4<T>& other);
		SgMatrix4<T>& operator=(const SgMatrix4<T>& rhs);

		bool IsEqual(const SgMatrix4<T>& rhs);
		SgMatrix4<T> Inverse() const;
		SgMatrix4<T> Transpose() const;
		T Determinant() const;

		bool operator== (const SgMatrix4<T>& rhs){return this == &rhs;}
		bool operator != (const SgMatrix4<T>& rhs){return !operator==(rhs);}
		T* operator[](int row){return m[row];}
		const T* operator[] (int row)const {return m[row];}
        friend SgMatrix4<T> operator * (const SgMatrix4<T> &lfs, const SgMatrix4<T> &rhs);
        friend SgMatrix4<T> operator * (const SgMatrix4<T> &lfs, T rhs);
        friend SgMatrix4<T> operator * (T lfs, const SgMatrix4<T> &rhs);
        friend SgMatrix4<T> operator + (const SgMatrix4<T> &lfs, const SgMatrix4<T> &rhs);
        friend SgMatrix4<T> operator - (const SgMatrix4<T> &lfs, const SgMatrix4<T> &rhs);

        
    
        friend std::ostream& operator << (std::ostream &os, const SgMatrix4 &m)
        {
            os << "[" <<  m[0][0] << " " <<  m[0][1] << " " <<  m[0][2] << " " <<  m[0][3] << "\n"
            << " "<<  m[1][0] << " " <<  m[1][1] << " " <<  m[1][2] << " " <<  m[1][3] << "\n"
            << " "<<  m[2][0] << " " <<  m[2][1] << " " <<  m[2][2] << " " <<  m[2][3] << "\n"
            << " "<<  m[3][0] << " " <<  m[3][1] << " " <<  m[3][2] << " " <<  m[3][3] << "])" << std::endl;
            return os;
        }
	};
    typedef SgMatrix4<float> Mat4f;
}

#endif /* Sgmath_hpp */
