#ifndef I_CLOCK_H
#define I_CLOCK_H

#include <stdint.h>

namespace stickman_common
{
	class Igame_clock
	{
	public:
		virtual void init() = 0;
		virtual void update() = 0;

		virtual void getTimeDelta(double *timeDelta) = 0;
		virtual void getFPS(int64_t *fps) = 0;
		virtual void getCPUCyclesDelta(int64_t *cyclesDelta) = 0;

		virtual bool isInitialized() = 0;
	};
}

#endif // I_CLOCK_H