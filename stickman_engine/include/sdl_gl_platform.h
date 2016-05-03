#ifndef SDL_GL_PLATFORM_H
#define SDL_GL_PLATFORM_H

struct SDL_Window;

namespace stickman_engine
{
	
	class sdl_gl_platform
	{
	public:
		sdl_gl_platform();

		bool init(int winW, int winH);
		void cleanup();

		void update();

	private:
		SDL_Window * _window;
		void* _glContext;

		int _winW;
		int _winH;
	};
}
#endif // SDL_GL_PLATFORM_H
