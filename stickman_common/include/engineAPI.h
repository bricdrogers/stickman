#ifndef ENGINE_API_H
#define ENGINE_API_H

#include "platform.h"
#include "assembly_info.h"
#include "game_assets.h"

namespace stickman_common
{
	class engineAPI
	{
	public:
		engineAPI(platform_io *platformIO, assembly_info *assInfo);

		platform_io *engine_io;
		assembly_info *assemblyInfo;
		game_assets *assets;
	};
}

#endif // ENGINE_API_H