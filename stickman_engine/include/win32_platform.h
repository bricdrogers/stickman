#ifndef WIN32_PLATFORM_H
#define WIN32_PLATFORM_H

#include<Windows.h>

#include "callback.h"
#include "game_memory.h"
#include "game_code.h"
#include "game_buffer.h"

namespace stickman_engine
{
	using namespace stickman_common;

	class win32_platform
	{
	public:
		win32_platform();

		bool init();
		void initGL(HWND window);
		void run();

		LRESULT CALLBACK handleWinProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

	private:
		inline void getClientSize(HWND hwnd, int * width, int * height)
		{
			RECT clientRect;
			GetClientRect(hwnd, &clientRect);
			*width = clientRect.right - clientRect.left;
			*height = clientRect.bottom - clientRect.top;
		}

		void createAssemblyInfo(assembly_info *assInfo);
		void paintWindow(HDC deviceContext);
		void resizeDIBSection(int width, int height);
	
		int _clientWidth;
		int _clientHeight;
		bool _isRunning;

		HWND _windowHandle;

		// paint storage
		BITMAPINFO _bitmapInfo;
		game_buffer _backBuffer;

		game_code _gameCode;		 // pointer to the gamecode
		game_memory _gameMemory;	 // game memory
	};
}

#endif // WIN32_PLATFORM_H