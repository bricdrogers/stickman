// External includes
#include <windows.h>

// Internal Includes
#include "win32_clock.h"

namespace stickman_engine
{
	void win32_clock::init()
	{
		// We first need to determine the performance frequency
		LARGE_INTEGER queryTime;
		if(!QueryPerformanceFrequency(&queryTime))
		{
			// TODO: Logging Query Performance Failed! Your clock will not work"
			return;
		}

		// Record the frequency
		_frequency = queryTime.QuadPart;

		// Now we need to get an initial time in order to calculate new times
		QueryPerformanceCounter(&queryTime);

		// Record the start time
		_currentTime = queryTime.QuadPart;

		// Record the start cycles
		_currentCycles = __rdtsc();

		// Set the initialized flag
		_isInitialized = true;
	}

	void win32_clock::update()
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
		_timeDelta = ((1000*(elapsedTicks)) / double(_frequency));
		_fps = _frequency / elapsedTicks;
	}

	bool win32_clock::isInitialized()
	{
		return _isInitialized;
	}

	void win32_clock::getTimeDelta(double *timeDelta)
	{
		*timeDelta = _timeDelta;
	}

	void win32_clock::getFPS(int64_t *fps)
	{
		*fps = _fps;
	}

	void win32_clock::getCPUCyclesDelta(int64_t *cyclesDelta)
	{
		*cyclesDelta = _cyclesDelta;
	}
}