#ifndef Color_h
#define Color_h

namespace SoftRender{

	struct Color 
	{
		float R, G, B, A;
		Color():R(1.0), G(1.0), B(1.0), A(1.0){}
		Color(float r, float g, float b, float a):R(r), G(g),B(b),A(a){}
		Color(float r, float g, float b):R(r), G(g), B(b), A(1.0){}

		Color operator+(Color& rhs){ return Color(R+rhs.R, G + rhs.G, B+rhs.B, A + rhs.A);}
		Color operator-(Color& rhs){ return Color(R-rhs.R, G - rhs.G, B - rhs.B, A - rhs.A);}
		Color operator*(Color& rhs){ return Color(R*rhs.R, G * rhs.G, B * rhs.B, A * rhs.A);}
		Color operator*(float f){ return Color(R*f, G*f, B*f, A*f);}
	};

}

#endif