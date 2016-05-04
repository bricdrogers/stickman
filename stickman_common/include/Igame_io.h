#ifndef I_GAME_IO_H
#define I_GAME_IO_H

#include <stdint.h>

namespace stickman_common
{
	class Igame_io
	{
	public:
		virtual void *readFile(char *fileName, int32_t *out_Size) = 0;
		virtual bool writeFile(char *fileName, uint32_t fileSize, void *memory) = 0;
	};
}

#endif // I_CLOCK_H