#include "stickman_external.h"

using namespace stickman_game;

// Initialize globals
stickman_game::stickman* _game = nullptr;

extern "C" __declspec(dllexport) GAME_INITIALIZE(GameInitialize)
{
	// Create a new instance of stickman
	_game = new stickman();

	if (_game == nullptr)
	{
		// TODO: Log error
		return false;
	}

	return _game->initialize(memory, engineAPI);
}

extern "C" __declspec(dllexport) GAME_UPDATE_AND_RENDER(GameUpdateAndRender)
{
	_game->update_and_render(memory, buffer);
}