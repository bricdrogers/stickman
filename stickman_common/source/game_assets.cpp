#include "game_assets.h"

namespace stickman_common
{
	game_assets::game_assets(platform_io * engineIO, assembly_info* assInfo)
	{
		engine_io = engineIO;
		assemblyInfo = assInfo;
	}

	bitmap * game_assets::loadBitmap(const char* filePath)
	{
		std::string absolutePath = assemblyInfo->dataPath + filePath;

		int32_t bitmapFileSize;
		void * bitmapFile = engine_io->readFile(absolutePath.c_str(), &bitmapFileSize);

		if (bitmapFileSize <= 0)
		{
			// TODO: Unable to load file
			return false;
		}

		return new bitmap(bitmapFile);
	}
}