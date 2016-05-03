#ifndef IENGINE_H
#define IENGINE_H

//#include "sdl_gl_platform.h"
//#include "sdl_Input.h"
#include "Iplatform.h"
#include "game_code.h"
#include "game_buffer.h"
#include "Igame_clock.h"

namespace stickman_engine
{
	using namespace stickman_common;

	class engine
	{
	public:
		engine();

		bool init(Iplatform * platform);
		void run();
		void quit();

	private:
		void gameLoop();
		void cleanup();

		Iplatform *_platform;		// pointer to the platform
		Igame_clock *_gameClock;				// pointer to the game click
		Igame_io *_gameIO;			// pointer to the game io

		game_code *_gameCode;		// pointer to the gamecode
		game_memory _gameMemory;	// game memory
		game_buffer _gameBuffer;	// game buffer
		
		bool _isRunning;
	};
}
#endif