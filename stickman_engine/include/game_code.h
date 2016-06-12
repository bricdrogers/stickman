#ifndef GAME_CODE_H
#define GAME_CODE_H

#include "stickman_external.h"
#include "game_memory.h"
#include "engineAPI.h"


// Forward declare windows types to avoid
// having to include windows.h

struct HINSTANCE__;
typedef HINSTANCE__* HINSTANCE;
typedef HINSTANCE HMODULE;

namespace stickman_engine
{
	class game_code
	{
	public:
		game_code();

		bool load(game_memory *memory, engineAPI *engineAPI);
		bool reload(game_memory *memory, engineAPI *engineAPI);
		void unload();
		
		inline void updateAndRender(game_memory *memory, game_buffer *buffer)
		{
			if (_GameUpdateAndRenderFuncPtr != nullptr)
			{
				_GameUpdateAndRenderFuncPtr(memory, buffer);
			}
		}

		void cleanup();

	private:
		// Game function pointers
		game_update_and_render* _GameUpdateAndRenderFuncPtr;
		game_initialize* _GameInitializeFuncPtr;

		HMODULE _gameLib;
		bool _isLoaded;
	};
}


#endif