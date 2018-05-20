#include "test.h"
#include "Render.h"


using namespace SoftRender;
using namespace std;

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

	render.SetFrustum(M_PI_2, float(WIDTH)/(float)HEIGHT, 0.1f, 1000.0f);
	render.SetCamera(Vec3f(15.0f, 15.0f, 15.0f));
	Light light(
		Vec3f(0.0f, 0.0f, 100.0f),
		Color(0.2f, 0.2f, 0.2f),
		Color(0.5f, 0.5f, 0.5f),
		Color(1.0f, 1.0f, 1.0f)
	);
	render.SetLight(light);

	render.currentMode = Textured;
	Material m(
		Color(1.0f, 0.5f, 0.31f),
		Color(1.0f, 0.5f, 0.31f),
		Color(0.5f, 0.5f, 0.5f),
		32.0f);
 	render.currentMode = WireFrame;
 	Model sphere(std::string("../../res/cow.obj"), Vec3f(-20.0f, -20.0, 0.0), m);
 	render.DrawModel(sphere);

	//render.SetLight(light);
	render.currentMode = Textured;
	Model cube(std::string("../../res/nanosuit/nanosuit.obj"), Vec3f(-5.0f, -5, -5), m);
	render.DrawModel(cube);
//
////Users/acetian/Documents/GitWorkSpace/SoftRasterization/res/
//// 	render.currentMode = WireFrame;
//// 	Model cow(std::string("../res/crystal_maiden/crystal_maiden_econ.fbx"), Vec3f(50, -100, -100), Material());
//// 	render.DrawModel(cow);
//	render.currentMode = Textured;
//	Model nanosuit2(std::string("../res/crystal_maiden/crystal_maiden_econ.fbx"), Vec3f(-50, -175, -150), m);
// 	render.DrawModel(nanosuit2);
	//  	Model bunny(std::string("res/bunny.obj"), Vec3f(0, 5, 0), Material());
	//  	render.DrawModel(bunny, false, true);

	SaveTexture(render.frameBuffer, WIDTH, HEIGHT, "screenshot.jpg");
}

