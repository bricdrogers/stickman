#include "globals.h"

#ifdef  PLATFORM_WIN32_SDL

#include "sdl_gl_platform.h"

#include <Windows.h>
#include <SDL.h>	// Simple DirectMedia Layer
#include <GL/gl.h>		// OpenGL graphics


namespace stickman_engine
{
	sdl_gl_platform::sdl_gl_platform()
	{
		_window = nullptr;
		_glContext = nullptr;
	}

	void sdl_gl_platform::cleanup()
	{
		SDL_GL_DeleteContext(_glContext);
		SDL_DestroyWindow(_window);
		SDL_Quit();

		_glContext = nullptr;
		_window = nullptr;
	}

	bool sdl_gl_platform::init(int winW, int winH)
	{
		_winW = winW;
		_winH = winH;

		// Initialize SDL (SDL will init the OpenGL Context
		if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) < 0)
		{
			return false;
		}

		// *****************
		// Initialize video
		// *****************

		// Set up memory sizes
		SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
		SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
		SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
		SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);

		SDL_GL_SetAttribute(SDL_GL_ACCUM_RED_SIZE, 8);
		SDL_GL_SetAttribute(SDL_GL_ACCUM_GREEN_SIZE, 8);
		SDL_GL_SetAttribute(SDL_GL_ACCUM_BLUE_SIZE, 8);
		SDL_GL_SetAttribute(SDL_GL_ACCUM_ALPHA_SIZE, 8);

		// aa
		SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
		SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 2);

		/* Request opengl 3.2 context.
		* SDL doesn't have the ability to choose which profile at this time of writing,
		* but it should default to the core profile */
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);

		/* Turn on double buffering with a 24bit Z buffer.
		* You may need to change this to 16 or 32 for your system */
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
		SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
		//SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);

		// Set up the window (width, height, resolution of window, SDL display flags)
		// *****
		// Note: Use SDL_WINDOW_INPUT_GRABBED to force cursor to stay inside the window
		// *****
		_window = SDL_CreateWindow("Game Window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, _winW, _winH, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);

		if (_window == nullptr)
		{
			// TODO: Error unable to create window
			return false;
		}

		_glContext = SDL_GL_CreateContext(_window);

		/* This makes our buffer swap syncronized with the monitor's vertical refresh */
		SDL_GL_SetSwapInterval(1);

		return true;
	}

	void sdl_gl_platform::update()
	{
	}
}

#endif //  PLATFORM_WIN32_SDL