#ifndef WIN32_IO_H
#define WIN32_IO_H

#include "Igame_io.h"

namespace stickman_engine
{
	using namespace stickman_common;

	class win32_io : public Igame_io
	{
	public:
		void *readFile(char *fileName, int32_t *out_Size);
		bool writeFile(char *fileName, uint32_t fileSize, void *memory);
	};
}

#endif // WIN32_IO_H