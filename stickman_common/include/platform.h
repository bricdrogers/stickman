#ifndef PLATFORM_H
#define PLATFORM_H

#include <stdint.h>

namespace stickman_common
{
	// ***
	// IO
	// ***

	#define PLATFORM_READ_FILE(name) void *name(const char *fileName, int32_t *out_Size)
	typedef PLATFORM_READ_FILE(platform_read_file);

	#define PLATFORM_WRITE_FILE(name) bool name(const char *fileName, uint32_t fileSize, void *memory)		
	typedef PLATFORM_WRITE_FILE(platform_write_file);

	struct platform_io
	{
		platform_write_file * writeFile;
		platform_read_file * readFile;
	};
}

#endif
