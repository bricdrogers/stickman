#include "engineAPI.h"

namespace stickman_common
{
	engineAPI::engineAPI(platform_io *platformIO, assembly_info *assInfo)
	{
		engine_io = platformIO;
		assemblyInfo = assInfo;

		// Create the assets
		assets = new game_assets(engine_io, assemblyInfo);
	}
}