#ifndef Texture_h
#define Texture_h

#include <vector>

namespace SoftRender {
	struct Texture{
		int width, height;
		std::string path;
		std::string type;
			//std::cout << iu+iv*width << " ";
		
		Texture() {}
		Texture(int _width, int _height):width(_width),
			height(_height){}
	};
}
#endif