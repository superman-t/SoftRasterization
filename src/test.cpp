#include "test.h"
#include "Render.h"


using namespace SoftRender;
using namespace std;

//#define M_PI_2 1.57079632679489661923 
test::test(void)
{
}
 

test::~test(void)
{
}

void test::testMatrix()
{
	Mat4f a;
	a[0][0] = 3.567f;
	a[0][1] = 4.535f;
	a[0][2] = 5.9808f;
	a[2][1] = 3.0f;
	a[3][2] = 5.36985f;
	a[3][1] = 7.9087f;
	a[1][2] = 5.78f;


}

void test::testRender()
{
	const int WIDTH = 1024, HEIGHT = 768;
	Render render(WIDTH, HEIGHT);

	render.SetFrustum(M_PI_2, float(WIDTH)/(float)HEIGHT, 0.1f, 100.0f);
	render.SetCamera(Vec3f(15.0f, 15.0f, 15.0f), Vec3f());
	//render.SetLight(Vec3f(0.0f, 0.0f, 30.0f), Vec3f(0.5f, 0.0f, 0.0f), Vec3f(0.8f, 0.8f, 0.8f), Vec3f(0.5f, 0.5f, 0.5f));

// 	Model sphere(std::string("res/sphere.obj"), Vec3f(2.5, 0.5, 1.5), Material());
//    	render.DrawModel(sphere, true, false);

// 	Model cube(std::string("res/cube.obj"), Vec3f(-2, 0, 2.0), Material());
// 	render.DrawModel(cube, false, true);
//Users/acetian/Documents/GitWorkSpace/SoftRasterization/res/
	render.currentMode = WireFrame;
	Model cow(std::string("../res/cow.obj"), Vec3f(-5, -5, 0), Material());
	render.DrawModel(cow, false, true);
	render.currentMode = Textured;
	Model nanosuit2(std::string("../res/nanosuit/nanosuit.obj"), Vec3f(5, -15, 0), Material());
	render.DrawModel(nanosuit2, false, true);
	//  	Model bunny(std::string("res/bunny.obj"), Vec3f(0, 5, 0), Material());
	//  	render.DrawModel(bunny, false, true);

	SaveTexture(render.frameBuffer, WIDTH, HEIGHT, "screenshot.jpg");
}

