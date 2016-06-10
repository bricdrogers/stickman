#ifndef I_GAME_IO_H
#define I_GAME_IO_H

#include "callback.h"
#include <stdint.h>
#include <string>

namespace stickman_common
{

	#define PLATFORM_READ_FILE(name) void *name(const char *fileName, int32_t *out_Size)
	typedef PLATFORM_READ_FILE(platform_read_file);										

	#define PLATFORM_WRITE_FILE(name) bool name(const char *fileName, uint32_t fileSize, void *memory)		
	typedef PLATFORM_WRITE_FILE(platform_write_file);		

	struct assembly_info
	{
		std::string exeFilePath;
	};

	class platform
	{
	public:		
		platform_write_file * writeFile;
		platform_read_file * readFile;

		assembly_info * assemblyInfo;
	};
}

#endif // I_CLOCK_H