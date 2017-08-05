//
//  Sgmath.cpp
//  Sgraphic
//
//  Created by AceTian on 2017/8/1.
//
//

#include <string>
#include <cstdlib>
#include "Sgmath.hpp"

namespace SoftRender{
    template <typename T>
	SgMatrix4<T>::SgMatrix4(const SgMatrix4<T>& other)
	{
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				m[i][j] = other[i][j];
			}
		}
	}

    template <typename T>
	SgMatrix4<T>::SgMatrix4(Vec4<T>&x, Vec4<T>& y, Vec4<T>&z)
	{
		for(int i = 0; i < 4; i++)
		{
			m[0][i] = x[i];
			m[1][i] = y[i];
			m[2][i] = z[i];
		}
	}

    template <typename T>
	SgMatrix4<T>::SgMatrix4(Vec4<T>&x, Vec4<T>& y, Vec4<T>&z, Vec4<T>& w )
	{
		for(int i = 0; i < 4; i++)
		{
            m[0][i] = x[i];
            m[1][i] = y[i];
            m[2][i] = z[i];
			m[3][i] = w[i];
		}
	}

    template <typename T>
	T SgMatrix4<T>::Determinant() const
	{
		return ((m[0][0]*m[1][1] - m[1][0]*m[0][1])
				*(m[2][2]*m[3][3] - m[3][2]*m[2][3])
				-(m[0][0]*m[2][1] - m[2][0]*m[0][1])
				*(m[1][2]*m[3][3] - m[3][2]*m[1][3])
				+(m[0][0]*m[3][1] - m[3][0]*m[0][1])
				*(m[1][2]*m[2][3] - m[2][2]*m[1][3])
				+(m[1][0]*m[2][1] - m[2][0]*m[1][1])
				*(m[0][2]*m[3][3] - m[3][2]*m[0][3])
				-(m[1][0]*m[3][1] - m[3][0]*m[1][1])
				*(m[0][2]*m[2][3] - m[2][2]*m[0][3])
				+(m[2][0]*m[3][1] - m[3][0]*m[2][1])
				*(m[0][2]*m[1][3] - m[1][2]*m[0][3]));
	}

	//inverse matrix
    template <typename T>
	SgMatrix4<T> SgMatrix4<T>::Inverse() const
	{
		SgMatrix4<T> r;
		T d = Determinant();
		if (abs(d) < 0.001)
		{
			return r;
		}else
		{
			d = 1.0/d;
        
			r[0][0] = d * (m[1][1] * (m[2][2] * m[3][3] - m[3][2] * m[2][3]) +
							m[2][1] * (m[3][2] * m[1][3] - m[1][2] * m[3][3]) +
							m[3][1] * (m[1][2] * m[2][3] - m[2][2] * m[1][3]));
        
			r[1][0] = d * (m[1][2] * (m[2][0] * m[3][3] - m[3][0] * m[2][3]) +
							m[2][2] * (m[3][0] * m[1][3] - m[1][0] * m[3][3]) +
							m[3][2] * (m[1][0] * m[2][3] - m[2][0] * m[1][3]));
        
			r[2][0] = d * (m[1][3] * (m[2][0] * m[3][1] - m[3][0] * m[2][1]) +
							m[2][3] * (m[3][0] * m[1][1] - m[1][0] * m[3][1]) +
							m[3][3] * (m[1][0] * m[2][1] - m[2][0] * m[1][1]));
        
			r[3][0] = d * (m[1][0] * (m[3][1] * m[2][2] - m[2][1] * m[3][2]) +
							m[2][0] * (m[1][1] * m[3][2] - m[3][1] * m[1][2]) +
							m[3][0] * (m[2][1] * m[1][2] - m[1][1] * m[2][2]));
        
			r[0][1] = d * (m[2][1] * (m[0][2] * m[3][3] - m[3][2] * m[0][3]) +
							m[3][1] * (m[2][2] * m[0][3] - m[0][2] * m[2][3]) +
							m[0][1] * (m[3][2] * m[2][3] - m[2][2] * m[3][3]));
        
			r[1][1] = d * (m[2][2] * (m[0][0] * m[3][3] - m[3][0] * m[0][3]) +
							m[3][2] * (m[2][0] * m[0][3] - m[0][0] * m[2][3]) +
							m[0][2] * (m[3][0] * m[2][3] - m[2][0] * m[3][3]));
        
			r[2][1] = d * (m[2][3] * (m[0][0] * m[3][1] - m[3][0] * m[0][1]) +
							m[3][3] * (m[2][0] * m[0][1] - m[0][0] * m[2][1]) +
							m[0][3] * (m[3][0] * m[2][1] - m[2][0] * m[3][1]));
        
			r[3][1] = d * (m[2][0] * (m[3][1] * m[0][2] - m[0][1] * m[3][2]) +
							m[3][0] * (m[0][1] * m[2][2] - m[2][1] * m[0][2]) +
							m[0][0] * (m[2][1] * m[3][2] - m[3][1] * m[2][2]));
        
			r[0][2] = d * (m[3][1] * (m[0][2] * m[1][3] - m[1][2] * m[0][3]) +
							m[0][1] * (m[1][2] * m[3][3] - m[3][2] * m[1][3]) +
							m[1][1] * (m[3][2] * m[0][3] - m[0][2] * m[3][3]));
        
			r[1][2] = d * (m[3][2] * (m[0][0] * m[1][3] - m[1][0] * m[0][3]) +
							m[0][2] * (m[1][0] * m[3][3] - m[3][0] * m[1][3]) +
							m[1][2] * (m[3][0] * m[0][3] - m[0][0] * m[3][3]));
        
			r[2][2] = d * (m[3][3] * (m[0][0] * m[1][1] - m[1][0] * m[0][1]) +
							m[0][3] * (m[1][0] * m[3][1] - m[3][0] * m[1][1]) +
							m[1][3] * (m[3][0] * m[0][1] - m[0][0] * m[3][1]));
        
			r[3][2] = d * (m[3][0] * (m[1][1] * m[0][2] - m[0][1] * m[1][2]) +
							m[0][0] * (m[3][1] * m[1][2] - m[1][1] * m[3][2]) +
							m[1][0] * (m[0][1] * m[3][2] - m[3][1] * m[0][2]));
        
			r[0][3] = d * (m[0][1] * (m[2][2] * m[1][3] - m[1][2] * m[2][3]) +
							m[1][1] * (m[0][2] * m[2][3] - m[2][2] * m[0][3]) +
							m[2][1] * (m[1][2] * m[0][3] - m[0][2] * m[1][3]));
        
			r[1][3] = d * (m[0][2] * (m[2][0] * m[1][3] - m[1][0] * m[2][3]) +
							m[1][2] * (m[0][0] * m[2][3] - m[2][0] * m[0][3]) +
							m[2][2] * (m[1][0] * m[0][3] - m[0][0] * m[1][3]));
        
			r[2][3] = d * (m[0][3] * (m[2][0] * m[1][1] - m[1][0] * m[2][1]) +
							m[1][3] * (m[0][0] * m[2][1] - m[2][0] * m[0][1]) +
							m[2][3] * (m[1][0] * m[0][1] - m[0][0] * m[1][1]));
        
			r[3][3] = d * (m[0][0] * (m[1][1] * m[2][2] - m[2][1] * m[1][2]) +
							m[1][0] * (m[2][1] * m[0][2] - m[0][1] * m[2][2]) +
							m[2][0] * (m[0][1] * m[1][2] - m[1][1] * m[0][2]));
        
		}
    
		return r;
    
	}

	//矩阵转置
    template <typename T>
	SgMatrix4<T> SgMatrix4<T>::Transpose() const
	{
		SgMatrix4<T> r;
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				r[i][j] = m[j][i];
			}
		}
		return r;
	}
    
    template <typename T>
    bool SgMatrix4<T>::IsEqual(const SgMatrix4<T>& rhs)
	{
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				if (m[i][j] !=rhs.m[i][j])
					return false;
			}
		}
		return true;
	}

    template <typename T>
	SgMatrix4<T>& SgMatrix4<T>::operator=(const SgMatrix4& rhs)
	{
		if (this == &rhs) return *this;
    
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				m[i][j] = rhs.m[i][j];
			}
		}
		return *this;
	}

    template <typename T>
	SgMatrix4<T> operator+(const SgMatrix4<T> &lfs, const SgMatrix4<T> & rhs)
	{
		SgMatrix4<T> r;
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				r[i][j] = lfs[i][j] + rhs[i][j];
			}
		}
		return r;
	}

    template <typename T>
	SgMatrix4<T> operator-(const SgMatrix4<T>& lfs, const SgMatrix4<T> & rhs)
	{
		SgMatrix4<T> r;
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				r[i][j] = lfs[i][j] - rhs[i][j];
			}
		}
		return r;
	}

    template <typename T>
	SgMatrix4<T> operator* (const SgMatrix4<T> &lfs, const SgMatrix4<T> &rhs)
	{
		SgMatrix4<T> r;
		for( int i = 0; i < 4; i++) 
		{
			for (int j = 0; j < 4; j++)
			{
				T t = 0.0f;
				for(int k = 0; k < 4; k++)
					t += lfs[i][k]*rhs[k][j];
				r[i][j] = t;
			}
		}
		return r;
	}

    template <typename T>
	SgMatrix4<T> operator*(const SgMatrix4<T>& lfs, T rhs)
	{
		SgMatrix4<T> r;
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				r[i][j] = lfs[i][j] * rhs;
			}
		}
		return r;
	}
    
    template <typename T>
	SgMatrix4<T> operator*(T lfs, const SgMatrix4<T>& rhs)
	{
		SgMatrix4<T> r;
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				r[i][j] = rhs[i][j] * lfs;
			}
		}
		return r;
	}
}
