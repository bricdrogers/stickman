#ifndef GAME_ASSETS_H
#define GAME_ASSETS_H

#include "platform.h"
#include "assembly_info.h"
#include "bitmap.h"

namespace stickman_common
{
	class game_assets
	{
	public:
		game_assets(platform_io * engineIO, assembly_info* assInfo);

		bitmap *loadBitmap(const char *filePath);

	private:
		platform_io *engine_io;
		assembly_info *assemblyInfo;
	};
}

#endif // GAME_ASSETS_H
