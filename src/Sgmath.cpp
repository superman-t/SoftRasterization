//
//  Sgmath.cpp
//  Sgraphic
//
//  Created by AceTian on 2017/8/1.
//
//

#include <string>
#include <stdlib.h>
#include "Sgmath.hpp"

namespace Sr{
	using namespace std;

	SgMatrix4::SgMatrix4(const SgMatrix4& other)
	{
		std::cout << "copy SgMatrix4" << std::endl;
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				m[i][j] = other[i][j];
			}
		}
	}

	SgMatrix4::SgMatrix4(Vector4&x, Vector4& y, Vector4&z)
	{
		for(int i = 0; i < 4; i++)
		{
			m[0][i] = x[i];
			m[1][i] = y[i];
			m[2][i] = z[i];
		}
	}

	SgMatrix4::SgMatrix4(Vector4&x, Vector4& y, Vector4&z, Vector4& w )
	{
		SgMatrix4(x, y, z);
		for(int i = 0; i < 4; i++)
		{
			m[3][i] = w[i];
		}
	}



	float SgMatrix4::Determinant() const
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
	SgMatrix4 SgMatrix4::Inverse() const
	{
		SgMatrix4 r;
		float d = Determinant();
		if (abs(int(d)) < 0.001)
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
	SgMatrix4 SgMatrix4::Transpose() const
	{
		SgMatrix4 r;
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				r[i][j] = m[j][i];
			}
		}
		return r;
	}
	ostream &operator<<(ostream &output, const SgMatrix4& other)
	{
    
		output << "SgMatrix4([" << other.m[0][0] << "\t" << other.m[0][1] << "\t" << other.m[0][2] << "\t" << other.m[0][3] << "\n"
		<< "\t "<< other.m[1][0] << "\t" << other.m[1][1] << "\t" << other.m[1][2] << "\t" << other.m[1][3] << "\n"
		<< "\t "<< other.m[2][0] << "\t" << other.m[2][1] << "\t" << other.m[2][2] << "\t" << other.m[2][3] << "\n"
		<< "\t "<< other.m[3][0] << "\t" << other.m[3][1] << "\t" << other.m[3][2] << "\t" << other.m[3][3] << "])" << std::endl;
    
		return output;
	}

	bool SgMatrix4::IsEqual(const SgMatrix4& rhs)
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

	SgMatrix4& SgMatrix4::operator=(const SgMatrix4& rhs)
	{
		std::cout << "assign SgMatrix4" << std::endl;
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

	SgMatrix4 operator+(const SgMatrix4 &lfs, const SgMatrix4 & rhs)
	{
		SgMatrix4 r;
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				r[i][j] = lfs[i][j] + rhs[i][j];
			}
		}
		return r;
	}

	SgMatrix4 operator-(const SgMatrix4& lfs, const SgMatrix4 & rhs) 
	{
		SgMatrix4 r;
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				r[i][j] = lfs[i][j] - rhs[i][j];
			}
		}
		return r;
	}

	SgMatrix4 operator* (const SgMatrix4 &lfs, const SgMatrix4 &rhs) 
	{
		cout << "operator*" << endl;
		SgMatrix4 r;
		for( int i = 0; i < 4; i++) 
		{
			for (int j = 0; j < 4; j++)
			{
				float t = 0.0f;
				for(int k = 0; k < 4; k++)
					t += lfs[i][k]*rhs[k][j];
				r[i][j] = t;
			}
		}
		return r;
	}

	SgMatrix4 operator*(const SgMatrix4& lfs, float rhs)
	{
		SgMatrix4 r;
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				r[i][j] = lfs[i][j] * rhs;
			}
		}
		return r;
	}
	SgMatrix4 operator*(float lfs, const SgMatrix4& rhs)
	{
		SgMatrix4 r;
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				r[i][j] = rhs[i][j] * lfs;
			}
		}
		return r;
	}

	void SgMatrix4::Log() {
		printf("SgMatrix4([%8.2f % 8.2f % 8.2f % 8.2f\n"
				"\t % 8.2f % 8.2f % 8.2f % 8.2f\n"
				"\t % 8.2f % 8.2f % 8.2f % 8.2f\n"
				"\t % 8.2f % 8.2f % 8.2f % 8.2f])\n",
				m[0][0], m[0][1], m[0][2], m[0][3],
				m[1][0], m[1][1], m[1][2], m[1][3],
				m[2][0], m[2][1], m[2][2], m[2][3],
				m[3][0], m[3][1], m[3][2], m[3][3]);
	}


}