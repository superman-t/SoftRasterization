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
	class Matrix4
	{
	public:
		T m[4][4];
		Matrix4 (){ memset(m, 0, sizeof(m)); m[0][0] = m[1][1] = m[2][2] = m[3][3] = 1.0; }

		bool operator== (const Matrix4<T>& rhs){return this == &rhs;}
		bool operator != (const Matrix4<T>& rhs){return !operator==(rhs);}
		T* operator[](int row){return m[row];}
		const T* operator[] (int row)const {return m[row];}

		Matrix4(const Matrix4<T>& other)
		{
			for (int i = 0; i < 4; i++)
			{
				for (int j = 0; j < 4; j++)
				{
					m[i][j] = other[i][j];
				}
			}
		}

		Matrix4(Vec3<T>&x, Vec3<T>& y, Vec3<T>&z)
		{
			for(int i = 0; i < 3; i++)
			{
				m[0][i] = x[i];
				m[1][i] = y[i];
				m[2][i] = z[i];
			}
			m[3][0] = m[3][1] = m[3][2] = 0.0;
			m[0][3] = m[1][3] = m[2][3] = 0.0;
			m[3][3] = 1.0;
		}

		Matrix4(Vec3<T>&x, Vec3<T>& y, Vec3<T>&z, Vec3<T>& w )
		{
			for(int i = 0; i < 3; i++)
			{
				m[0][i] = x[i];
				m[1][i] = y[i];
				m[2][i] = z[i];
				m[3][i] = w[i];
			}
			m[0][3] = m[1][3] = m[2][3] = 0.0;
			m[3][3] = 1.0;
		}


		T Determinant() const
		{
			return T((m[0][0]*m[1][1] - m[1][0]*m[0][1])
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
		Matrix4<T> Inverse() const
		{
			Matrix4<T> r;
			T d = Determinant();
			if (std::abs(d) < 0.001)
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

		Matrix4<T> Transpose() const
		{
			Matrix4<T> r;
			for (int i = 0; i < 4; i++)
			{
				for (int j = 0; j < 4; j++)
				{
					r[i][j] = m[j][i];
				}
			}
			return r;
		}

		bool IsEqual(const Matrix4<T>& rhs)
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

		Matrix4<T>& operator=(const Matrix4& rhs)
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

		Matrix4<T> operator+(const Matrix4<T> & rhs)
		{
			Matrix4<T> r;
			for (int i = 0; i < 4; i++)
			{
				for (int j = 0; j < 4; j++)
				{
					r[i][j] = m[i][j] + rhs[i][j];
				}
			}
			return r;
		}

		Matrix4<T> operator-(const Matrix4<T> & rhs)
		{
			Matrix4<T> r;
			for (int i = 0; i < 4; i++)
			{
				for (int j = 0; j < 4; j++)
				{
					r[i][j] = m[i][j] - rhs[i][j];
				}
			}
			return r;
		}

		Matrix4<T> operator* ( const Matrix4<T> &rhs)
		{
			Matrix4<T> r;
			for( int i = 0; i < 4; i++) 
			{
				for (int j = 0; j < 4; j++)
				{
					T t = 0.0f;
					for(int k = 0; k < 4; k++)
						t += m[i][k]*rhs[k][j];
					r[i][j] = t;
				}
			}
			return r;
		}

		Matrix4<T> operator*(T rhs)
		{
			Matrix4<T> r;
			for (int i = 0; i < 4; i++)
			{
				for (int j = 0; j < 4; j++)
				{
					r[i][j] = m[i][j] * rhs;
				}
			}
			return r;
		}

		friend Matrix4<T> operator*(T lfs, const Matrix4<T>& rhs)
		{
			Matrix4<T> r;
			for (int i = 0; i < 4; i++)
			{
				for (int j = 0; j < 4; j++)
				{
					r[i][j] = rhs[i][j] * lfs;
				}
			}
			return r;
		}

		friend std::ostream& operator << (std::ostream &os, const Matrix4<T> &m)
        {
            os << "[" <<  m[0][0] << " " <<  m[0][1] << " " <<  m[0][2] << " " <<  m[0][3] << "\n"
            << " "<<  m[1][0] << " " <<  m[1][1] << " " <<  m[1][2] << " " <<  m[1][3] << "\n"
            << " "<<  m[2][0] << " " <<  m[2][1] << " " <<  m[2][2] << " " <<  m[2][3] << "\n"
            << " "<<  m[3][0] << " " <<  m[3][1] << " " <<  m[3][2] << " " <<  m[3][3] << "]" << std::endl;
            return os;
        }
	};
 	typedef Matrix4<float> Mat4f;   
}

#endif /* Sgmath_hpp */
