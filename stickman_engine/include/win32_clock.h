#ifndef WIN32_CLOCK_H
#define WIN32_CLOCK_H

#include <windows.h>
#include <stdint.h>

#include "Igame_clock.h"

namespace stickman_engine
{
	using namespace stickman_common;

	// TODO: Inline this class

	class win32_clock : public Igame_clock
	{	
		public:
			void init();
			void update();

			void getTimeDelta(double *timeDelta);
			void getFPS(int64_t *fps);
			void getCPUCyclesDelta(int64_t *cyclesDelta);

			inline double testfunc()
			{
				// record the current time
				int64_t oldTime = _currentTime;
				int64_t oldCycles = _currentCycles;

				// Grab the processor cycles
				_currentCycles = __rdtsc();

				// Grab the processor time
				LARGE_INTEGER queryTime;
				QueryPerformanceCounter(&queryTime);

				// Record the current time
				_currentTime = queryTime.QuadPart;

				int64_t elapsedTicks = _currentTime - oldTime;
				_cyclesDelta = (_currentCycles - oldCycles) / 1000;

				// Im going to go ahead and calc the time delta here, it will probably be used multiple times per frame
				_timeDelta = ((1000 * (elapsedTicks)) / double(_frequency));
				_fps = _frequency / elapsedTicks;

				return _timeDelta;
			}

			inline double testfunc2()
			{
				double bleh = 100;
				bleh += 10000.0;
				return bleh;
			}

			inline double testfunc3()
			{
				double bleh = 100;
				bleh += 10000.0;
				return bleh;
			}

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