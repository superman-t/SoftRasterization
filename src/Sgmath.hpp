//
//  Sgmath.hpp
//  Sgraphic
//
//  Created by AceTian on 2017/8/1.
//
//

#ifndef Sgmath_hpp
#define Sgmath_hpp

#include <stdio.h>
#include <iostream>
#include <string>

using namespace std;
struct SgMatrix4
{
    float m[4][4];
    SgMatrix4 ()
    {
        memset(m, 0, sizeof(m));
        m[0][0] = m[1][1] = m[2][2] = m[3][3] = 1.0;
    }
    
    
    SgMatrix4(const SgMatrix4& other);
    SgMatrix4& operator=(const SgMatrix4& rhs);
    
    bool IsEqual(const SgMatrix4& rhs);
    SgMatrix4 Inverse() const;
    SgMatrix4 Transpose() const;
    float Determinant() const;
    
    bool operator== (const SgMatrix4& rhs){return this == &rhs;}
    bool operator != (const SgMatrix4& rhs){return !operator==(rhs);}
    float* operator[](int row){return m[row];}
    const float* operator[] (int row)const {return m[row];}
    
    void Log();
    
};
ostream& operator << (ostream &os, const SgMatrix4 &m);

SgMatrix4 operator * (const SgMatrix4 &lfs, const SgMatrix4 &rhs);
SgMatrix4 operator * (const SgMatrix4 &lfs, float rhs);
SgMatrix4 operator * (float lfs, const SgMatrix4 &rhs);
SgMatrix4 operator + (const SgMatrix4 &lfs, const SgMatrix4 &rhs);
SgMatrix4 operator - (const SgMatrix4 &lfs, const SgMatrix4 &rhs);


#endif /* Sgmath_hpp */
