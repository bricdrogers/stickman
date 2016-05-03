#ifndef STICKMAN_H
#define STICKMAN_H

#include "Igame_core.h"

using namespace stickman_common;

namespace stickman_game
{
	class stickman : public Igame_core
	{
	public:
		stickman();
		~stickman();

		bool initialize(game_memory *memory, Igame_io *gameIO);
		void update_and_render(game_memory *memory, game_buffer *buffer);

	protected:
	private:
		Igame_io *_gameIO;		// pointer to the platform independent io object
	};
}

#endif // STICKMAN_H