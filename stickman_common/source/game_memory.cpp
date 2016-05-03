#include "game_memory.h"

namespace stickman_common
{
	game_state * game_memory::getGameState()
	{
		return (game_state*)persistantStorage;
	}
}