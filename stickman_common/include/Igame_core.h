#ifndef GAME_CORE_H
#define GAME_CORE_H

#include "game_memory.h"
#include "game_buffer.h"
#include "Igame_io.h"

namespace stickman_common
{
	class Igame_core
	{
	public:
		virtual bool initialize(game_memory *memory, Igame_io *gameIO) = 0;
		virtual void update_and_render(game_memory *memory, game_buffer *buffer) = 0;
	};
}
#endif

