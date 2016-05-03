#ifndef WIN32_PLATFORM_H
#define WIN32_PLATFORM_H

#include "Iplatform.h"
#include "Igame_clock.h"
#include "callback.h"
#include "game_memory.h"
#include "game_buffer.h"
#include "Igame_io.h"

namespace stickman_engine
{
	using namespace stickman_common;

	class win32_platform : public Iplatform
	{
	public:
		win32_platform();

		bool init(int winW, int winH, Igame_clock **clock, Igame_io **gameIO, game_memory *memory, game_buffer *buffer);
		bool update();

		void bindQuitCallback(callback0* cb);


		LRESULT CALLBACK handleWinProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

	private:
		void resizeDIBSection(int width, int height);
		void paintWindow(HDC deviceContext);
		void getClientSize(HWND hwnd, int * width, int * height);

		callback0* _quitCallback;		// Callback to quit the game

		int _clientWidth;
		int _clientHeight;

		HWND _windowHandle;

		// paint storage
		BITMAPINFO _bitmapInfo;
		game_buffer * _backBuffer;	// Id really prefer to not store this
	};
}

#endif // WIN32_PLATFORM_H