#include "stickman_external.h"
#include <iostream>

using namespace stickman_game;

// Initialize globals
stickman_common::Igame_core * _game_core = nullptr;
bool mInitialize = false;

extern "C" __declspec(dllexport) GAME_INITIALIZE(GameInitialize)
{
	// Create a new instance of stickman
	_game_core = new stickman();

	if (_game_core == nullptr)
	{
		// TODO: Log error
		return;
	}

	mInitialize = _game_core->initialize(memory, gameIO); 	// Set the initialized flag.
}

extern "C" __declspec(dllexport) GAME_UPDATE_AND_RENDER(GameUpdateAndRender)
{
	if (mInitialize == true)
	{
		_game_core->update_and_render(memory, buffer);
	}
}