#ifndef Texture_h
#define Texture_h

#include <vector>

namespace SoftRender {
	struct Texture{
		int width, height;
		std::string path;
		std::vector<Color> data;
		Color Map(float u, float v){
			int width = 256, height = 256;
			u = std::min (1.0f, std::max (0.0f, u));
			v = std::min (1.0f, std::max (0.0f, v));
			unsigned int iu = int(u*(width))%(width);
			unsigned int iv = int(v*(height))%(height);
			//std::cout << iu+iv*width << " ";
			return data[iu+iv*width];
		}
		Texture() {}
		Texture(int _width, int _height, std::vector<Color> _data):width(_width),
			height(_height), data(_data){}
	};
}
#endif