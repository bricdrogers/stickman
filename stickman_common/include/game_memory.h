#ifndef GAME_MEMORY_H
#define GAME_MEMORY_H

#include<stdint.h>
#include "game_state.h"

#define KILOBYTES(value) (value * 1024)
#define MEGABYTES(value) (KILOBYTES(value) * 1024)
#define GIGABYTES(value) (MEGABYTES(value) * 1024)
#define TERABYTES(value) (GIGABYTES(value) * 1024)

namespace stickman_common
{
	struct game_memory
	{
	public:
		// Game State Storage
		uint64_t persistantStorageSize;
		void * persistantStorage;

		// Scratch Space storage
		uint64_t transientStorageSize;
		void * transientStorage;

		game_state* getGameState();
	};
}


#endif