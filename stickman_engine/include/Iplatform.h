#ifndef I_PLATFORM_H
#define I_PLATFORM_H

#include "callback.h"
#include "game_memory.h"
#include "game_buffer.h"
#include "Igame_io.h"
#include "Igame_clock.h"

namespace stickman_engine
{
	using namespace stickman_common;

	class Iplatform
	{
	public:
		virtual bool init(int winW, int winH, Igame_clock **clock, Igame_io **gameIO, game_memory *memory, game_buffer *buffer) = 0;
		virtual bool update() = 0;

		virtual void bindQuitCallback(callback0* cb) = 0;
	};
}


#endif // I_PLATFORM_H