#ifndef I_GAME_IO_H
#define I_GAME_IO_H

#include "callback.h"
#include <stdint.h>

namespace stickman_common
{

	#define PLATFORM_READ_FILE(name) void *name(char *fileName, int32_t *out_Size)
	typedef PLATFORM_READ_FILE(platform_read_file);										

	#define PLATFORM_WRITE_FILE(name) void *name(char *fileName, uint32_t fileSize, void *memory)		
	typedef PLATFORM_WRITE_FILE(platform_write_file);													

	class platform
	{
	public:		
		platform_write_file * writeFile;
		platform_read_file * readFile;
	};
}

#endif // I_CLOCK_H