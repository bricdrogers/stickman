#include "globals.h"

#ifdef PLATFORM_WIN32

#include <Windows.h>
#include<stdint.h>
#include "win32_platform.h"
#include "win32_io.h"

using namespace stickman_engine;
using namespace stickman_common;

// WinMain entry point
int wmain(int argc, char *argv[])
{
	win32_platform platform;

	if (!platform.init())
	{
		// TODO: Log error
		return -1;
	}

	platform.run();

	return 0;
}

// Main windows callback
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	win32_platform * instancePtr = reinterpret_cast<win32_platform*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));

	if (instancePtr != nullptr)
	{
		return instancePtr->handleWinProc(hwnd, uMsg, wParam, lParam);
	}
	// If our instance does not exist, just handle the defaults
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

namespace stickman_engine
{
	win32_platform::win32_platform()
	{
		_windowHandle = nullptr;
	}

	bool win32_platform::init()
	{
		// Use default size for now
		int32_t winW = 0;
		int32_t winH = 0;

		// Define the window
		WNDCLASS windowClass = {};

		// https://msdn.microsoft.com/en-us/library/windows/desktop/ff729176%28v=vs.85%29.aspx
		// CS_OWNDC - Tells windows that we want a unique DC that we will not be releasing (not shared)
		// CS_HREDRAW - Redraw if height is changed
		// CS_VREDRAW - Redraw if width is changed
		windowClass.style = CS_OWNDC | CS_HREDRAW | CS_VREDRAW;
		windowClass.lpfnWndProc = WindowProc;
		windowClass.hInstance = GetModuleHandle(NULL);
		windowClass.lpszClassName = "stickmanWindow";
		//windowClass.hIcon = TODO Create ICON

		if (RegisterClass(&windowClass))
		{
			// Create the window
			//https://msdn.microsoft.com/en-us/library/windows/desktop/ms632680%28v=vs.85%29.aspx
			_windowHandle = CreateWindowEx(0,
				windowClass.lpszClassName,
				"Stickman",
				WS_OVERLAPPEDWINDOW | WS_VISIBLE,
				CW_USEDEFAULT,
				CW_USEDEFAULT,
				(winW != 0) ? winW : CW_USEDEFAULT,
				(winW != 0) ? winW : CW_USEDEFAULT,
				0,
				0,
				windowClass.hInstance,
				0);

			if (_windowHandle == nullptr)
			{
				// TODO: Logging unable to create window
				return false;
			}

			// Embed a pointer to the win32_platform instance so we can process the
			// win proc function in a object oriented way
			SetWindowLongPtr(_windowHandle, GWLP_USERDATA, (LONG_PTR)this);

			getClientSize(_windowHandle, &_clientWidth, &_clientHeight);
			resizeDIBSection(_clientWidth, _clientHeight);
		}
		else
		{
			// TODO: Logging unable to register class
			return false;
		}


		// Allocate the game memory
#ifdef STICKMAN_INTERNAL
		LPVOID baseAddress = (LPVOID)TERABYTES((uint64_t)2);
#else
		LPVOID baseAddress = 0;
#endif

		_gameMemory.persistantStorageSize = MEGABYTES(64);
		_gameMemory.transientStorageSize = GIGABYTES((uint64_t)1);

		// TODO: Get MEM_LARGE_PAGES working as this will allow use to have up to 2mb pages which gives up a small boost in the CPU TLB
		_gameMemory.persistantStorage = VirtualAlloc(baseAddress, _gameMemory.persistantStorageSize + _gameMemory.transientStorageSize, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
		_gameMemory.transientStorage = (uint8_t *)(_gameMemory.persistantStorage) + _gameMemory.persistantStorageSize;

		// Create and initialize the gameIO object
		platform *platformAPI = new platform();

		// Initialize the game code
		if (_gameCode.load(&_gameMemory, platformAPI) == false)
		{
			// TODO: Error unable to load gamecode
			return false;
		}

		return true;
	}

	void win32_platform::run()
	{
		_isRunning = true;

		// We first need to determine the performance frequency
		int64_t clockFrequency = 0;
		int64_t currentTime, currentCycles;
		{
			LARGE_INTEGER queryTime = {};
			if (QueryPerformanceFrequency(&queryTime))
			{
				// TODO: Logging Query Performance Failed! Your clock will not work"
				clockFrequency = queryTime.QuadPart;
			}

			// Initialize the time
			QueryPerformanceCounter(&queryTime);
			currentTime = queryTime.QuadPart;

			// Initialize the cycles
			currentCycles = __rdtsc();
		}


		while (_isRunning == true)
		{
			// Paint the back buffer to the screen
			MSG message;
			while (PeekMessage(&message, nullptr, 0, 0, PM_REMOVE))
			{
				if (message.message == WM_QUIT)
				{
					// Stop processing messages
					return;
				}

				TranslateMessage(&message);
				DispatchMessage(&message);
			}

			_gameCode.updateAndRender(&_gameMemory, &_backBuffer);

			// paint the buffer to the window
			HDC deviceContext = GetDC(_windowHandle);
			paintWindow(deviceContext);
			ReleaseDC(_windowHandle, deviceContext);

			// *******
			// Frame Stats
			// *******
			int64_t oldTime = currentTime;
			int64_t oldCycles = currentCycles;

			// Grab the processor cycles
			currentCycles = __rdtsc();

			LARGE_INTEGER queryTime;
			QueryPerformanceCounter(&queryTime);
			currentTime = queryTime.QuadPart;

			int64_t elapsedTicks = currentTime - oldTime;
			int64_t frameKiloCycles = (currentCycles - oldCycles) / 1000;
			int64_t framesPerSecond = clockFrequency / elapsedTicks;
			double frameElapsedMS = ((1000 * (elapsedTicks)) / double(clockFrequency));

			char buffer[256];
			wsprintf(buffer, "Milliseconds/frame: %dms. FPS: %d. Kilocycles/frame: %d\n", (int32_t)frameElapsedMS, (int32_t)framesPerSecond, (int32_t)frameKiloCycles);
			OutputDebugStringA(buffer);
		}
	}

	void win32_platform::paintWindow(HDC deviceContext)
	{
		// Blt the dib section with the option to scale
		// Note: this is bitblt with scaling
		StretchDIBits(deviceContext,
			0, 0, _clientWidth, _clientHeight,				// dest size
			0, 0, _backBuffer.width, _backBuffer.height,	// source size
			_backBuffer.memory,
			&_bitmapInfo,
			DIB_RGB_COLORS,			// DIB section will not use a palette
			SRCCOPY);				// copy the src to the dest
	}


	LRESULT CALLBACK win32_platform::handleWinProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		LRESULT result = 0;

		switch (uMsg)
		{
			// Standard Windows Notificatiosn
			// https://msdn.microsoft.com/en-us/library/windows/desktop/ff468922%28v=vs.85%29.aspx
			case WM_SIZE:
			{
				getClientSize(hwnd, &_clientWidth, &_clientHeight);
				resizeDIBSection(_clientWidth, _clientHeight);
				break;
			}

			case WM_CLOSE:
				_isRunning = false;
				break;

			case WM_DESTROY:
				_isRunning = false;
				break;

			case WM_ACTIVATEAPP:
				OutputDebugStringA("WM_ACTIVATEAPP\n");
				break;

			case WM_PAINT:
			{
				PAINTSTRUCT paint;
				HDC deviceContext = BeginPaint(hwnd, &paint);
				paintWindow(deviceContext);
				EndPaint(hwnd, &paint);

				break;
			}

			case WM_SYSKEYDOWN:
			case WM_SYSKEYUP:
			case WM_KEYDOWN:
			case WM_KEYUP:
			{
				uint64_t VKCode = wParam;		// virtual code

			}
			default:
				// Call the def window proc to handle unhandled messages
				result = DefWindowProc(hwnd, uMsg, wParam, lParam);
				break;
		}

		return result;
	}

	void win32_platform::resizeDIBSection(int width, int height)
	{
		// clean up the old bitmap
		if (_backBuffer.memory != nullptr)
		{
			VirtualFree(_backBuffer.memory, 0, MEM_RELEASE);
			_backBuffer.memory = nullptr;
		}

		_backBuffer.width = width;
		_backBuffer.height = height;
		_backBuffer.stride = width * 4;

		_bitmapInfo.bmiHeader.biSize = sizeof(_bitmapInfo.bmiHeader);
		_bitmapInfo.bmiHeader.biWidth = _backBuffer.width;
		_bitmapInfo.bmiHeader.biHeight = -_backBuffer.height;	// Negative so we can process top-down
		_bitmapInfo.bmiHeader.biPlanes = 1;

		// we really only need 24 bits for rgb
		// r - 8 bits, g - 8 bits, b - 8 bits
		// but this is only 3 bytes which the processor does not like
		// so, we use 32 bits per pixel to be byte aligned.
		_bitmapInfo.bmiHeader.biBitCount = 32;			// 32 bits per pixel
		_bitmapInfo.bmiHeader.biCompression = BI_RGB;	// no compression

		int bytesPerPixel = 4; // 32 bits
		_backBuffer.memory = VirtualAlloc(0, (_backBuffer.width * _backBuffer.height) * bytesPerPixel, MEM_COMMIT, PAGE_READWRITE);
	}
}

#endif // PLATFORM_WIN32 