#ifndef STICKMAN_H
#define STICKMAN_H

#include "game_memory.h"
#include "game_buffer.h"
#include "engineAPI.h"

using namespace stickman_common;

namespace stickman_game
{
	class stickman
	{
	public:
		stickman();
		~stickman();

		bool initialize(game_memory *memory, engineAPI *engineAPI);
		void update_and_render(game_memory *memory, game_buffer *buffer);

	protected:
	private:
		engineAPI *_engineAPI;		// pointer to the platform independent io object

		// TEMP
		bitmap * _testData;
	};
}

#endif // STICKMAN_H