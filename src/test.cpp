#include "test.h"
#include "Sgmath.hpp"
#include "Common.h"

using namespace Sr;
test::test(void)
{
}


test::~test(void)
{
}

void test::testMatrix()
{
	SgMatrix4 a;

	SgMatrix4 b(a);
	a[2][1] = 3.0;

	cout << a;
	cout << a.Transpose();
	SgMatrix4 c;
	c = a * b;
	cout << c ;
	cout << a-b ;
	cout << a+b ;
	cout << 2.0f*a;
	cout << a.Inverse();
	Vector4 d(1,2,3,0);
	cout << d*a;
	cout << Sgm::TransformDot(d, a);
	cout << (d*a == Sgm::TransformDot(d, a))<< endl;

}