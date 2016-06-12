#include "game_code.h"
#include <Windows.h>

namespace stickman_engine
{
	game_code::game_code()
	{
		// Initialize variables
		_gameLib = nullptr;
		_isLoaded = false;

		_GameUpdateAndRenderFuncPtr = nullptr;
		_GameInitializeFuncPtr = nullptr;	
	}

	void game_code::cleanup()
	{
		// unload the gamecode
		unload();

		_gameLib = nullptr;
	}

	bool game_code::load(game_memory *memory, engineAPI *engineAPI)
	{
		if (_isLoaded == true)
		{
			// TODO: Warning, game is already loaded
			return false;
		}

		// Try to hot-load the game.dll
		_gameLib = LoadLibraryA("stickman.dll");

		if (_gameLib == nullptr)
		{
			// TODO: Error logging
			return false;
		}

		// Assign function pointers
		_GameUpdateAndRenderFuncPtr = (game_update_and_render*)GetProcAddress(_gameLib, "GameUpdateAndRender");
		_GameInitializeFuncPtr = (game_initialize*)GetProcAddress(_gameLib, "GameInitialize");

		if (_GameInitializeFuncPtr == nullptr ||
			_GameUpdateAndRenderFuncPtr == nullptr)
		{
			// TODO: Error Logging. Unable to assign function pointers
			return false;
		}

		// Initialize the game
		_GameInitializeFuncPtr(memory, engineAPI);

		// Set the loaded flag
		_isLoaded = true;

		return true;
	}

	void game_code::unload()
	{
		if (_isLoaded == false)
		{
			// TODO: Log Warning. Game code is already unloaded
			return;
		}

		if (FreeLibrary(_gameLib) == false)
		{
			// TODO: LOG ERROR. Unable to free game code library
		}

		// Set pointers to null
		_gameLib = nullptr;
		_GameUpdateAndRenderFuncPtr = nullptr;
		_GameInitializeFuncPtr = nullptr;
	}

	bool game_code::reload(game_memory *memory, engineAPI *engineAPI)
	{
		// If game code is loaded, we need to unload the
		// library
		if (_isLoaded == true)
		{
			unload();
		}

		// Load the game code
		return load(memory, engineAPI);
	}
}