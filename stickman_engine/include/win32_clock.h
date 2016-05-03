/*
 * 	multiplatform click. (Currently only runs in win32
 *
 *  Created on: April 22, 2013
 *      Author: Bric Rogers
 */

#ifndef WIN32_CLOCK_H
#define WIN32_CLOCK_H

#include <stdint.h>

#include "Igame_clock.h"

namespace stickman_engine
{
	using namespace stickman_common;

	class win32_clock : public Igame_clock
	{	
		public:
			void init();
			void update();

			void getTimeDelta(double *timeDelta);
			void getFPS(int64_t *fps);
			void getCPUCyclesDelta(int64_t *cyclesDelta);

			bool isInitialized();

		private:
			int64_t _frequency;
			int64_t _currentTime;

			double _timeDelta;
			int64_t _fps;

			int64_t _currentCycles;
			int64_t _cyclesDelta;

			bool _isInitialized;
	};
}

#endif // WIN32_CLOCK_H