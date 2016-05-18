#ifndef WIN32_IO_H
#define WIN32_IO_H

#include "platform.h"

namespace stickman_engine
{
	using namespace stickman_common;

	class win32_io
	{
	public:
		void *readFile(char *fileName, int32_t *out_Size);
		bool writeFile(char *fileName, uint32_t fileSize, void *memory);

		PLATFORM_WRITE_FILE(Win32PlatformWriteFile)
		{

		}
	};
}

#endif // WIN32_IO_H