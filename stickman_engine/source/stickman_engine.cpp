#include "stickman_engine.h"
#include "callback.h"

#include <stdio.h>
#include "win32_clock.h"

namespace stickman_engine
{
	using namespace stickman_common;

	engine::engine()
	{
		_platform = nullptr;
		_gameCode = nullptr;
		_isRunning = false;

		_gameMemory = {};	// zero out the game memory
		_gameBuffer = {};	// zero out the game buffer
	}

	bool engine::init(Iplatform * platform)
	{
		// Create the quit callback
		callback0 *quitCallback = new callback0();
		quitCallback->bind(this, &engine::quit);

		// Create and Initialize the platform
		_platform = platform;
		if (_platform == nullptr || _platform->init(0, 0, &_gameClock, &_gameIO, &_gameMemory, &_gameBuffer) == false)
		{
			// TODO: Error unable to create platform layer
			return false;
		}

		// Verify that we have properly allocated some memory
		if (_gameMemory.persistantStorageSize <= 0 ||
			_gameMemory.transientStorageSize <= 0 ||
			_gameMemory.persistantStorage == nullptr ||
			_gameMemory.transientStorage == nullptr)
		{
			// TODO: Logging unable to allocate game memory
			return false;
		}

		// Verify that the clock has been properly initialized
		if (_gameClock == nullptr || !_gameClock->isInitialized())
		{
			// TODO: Logging unable to initialize game clock
			return false;
		}

		// Verify that the gameIO has been properly craeted
		if (_gameIO == nullptr)
		{
			// TODO: Unable to create the game IO
			return false;
		}

		_platform->bindQuitCallback(quitCallback);

		// Initialize the game code
		_gameCode = new game_code();
		if (_gameCode == nullptr || _gameCode->load(&_gameMemory, _gameIO) == false)
		{
			// TODO: Error unable to load gamecode
			return false;
		}

		return true;
	}

	void engine::quit()
	{
		_isRunning = false;
	}

	void engine::cleanup()
	{
		if (_gameCode != nullptr)
		{
			_gameCode->cleanup();

			delete _gameCode;
			_gameCode = nullptr;
		}
	}

	void engine::run()
	{
		_isRunning = true;

		gameLoop();

		// TODO: should we call cleanup here?
	}

	void engine::gameLoop()
	{
		while (_isRunning == true)
		{
			// Update the game clock
			_gameClock->update();
			_gameClock->testfunc();
			_gameClock->testfunc2();
			win32_clock *test1 = (win32_clock*)_gameClock;
			test1->testfunc3();
			test1->testfunc2();

			// TODO: Write a profiler and move this
			double timedelta;
			int64_t fps;
			int64_t cycles;
			_gameClock->getTimeDelta(&timedelta);
			_gameClock->getFPS(&fps);
			_gameClock->getCPUCyclesDelta(&cycles);

			char buffer[256];
			wsprintf(buffer, "Milliseconds/frame: %dms. FPS: %d. Kilocycles/frame: %d\n", (int32_t)timedelta, (int32_t)fps, (int32_t)cycles);
			OutputDebugStringA(buffer);

			// Update the platform, this is a faulure point
			if (!_platform->update())
			{
				// TODO: Logging unable to get platform update
				return;
			}

			_gameCode->updateAndRender(&_gameMemory, &_gameBuffer);
		}
	} 
}