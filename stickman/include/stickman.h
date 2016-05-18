#ifndef STICKMAN_H
#define STICKMAN_H

#include "game_memory.h"
#include "game_buffer.h"
#include "platform.h"

using namespace stickman_common;

namespace stickman_game
{
	class stickman
	{
	public:
		stickman();
		~stickman();

		bool initialize(game_memory *memory, platform *gameIO);
		void update_and_render(game_memory *memory, game_buffer *buffer);

	protected:
	private:
		platform *_gameIO;		// pointer to the platform independent io object
	};
}

#endif // STICKMAN_H