#ifndef TextureManager_h
#define TextureManager_h

#include <map>
#include <vector>
#include "Common.h"

namespace SoftRender
{
	class TextureManager
	{
	public:
		TextureManager* create();
		virtual ~TextureManager();

		bool LoadTexture (Texture &texture, std::string& file);
		void SaveTexture(std::vector<Color> &frameBuffer, int width, int height, std::string& file);

		static TextureManager* getInstance();
		std::vector<Color> getTexture(std::string& filepath);
		
		std::map<std::string, std::vector<Color>> textureMaps;
	};
}


#endif