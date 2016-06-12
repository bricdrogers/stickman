#ifndef WIN32_IO_H
#define WIN32_IO_H

#include <Windows.h>
#include "engineAPI.h"

namespace stickman_engine
{
	PLATFORM_WRITE_FILE(Win32PlatformWriteFile)
	{
		HANDLE fileHandle = CreateFileA(fileName, GENERIC_WRITE, 0, nullptr, CREATE_ALWAYS, 0, nullptr);
		if (fileHandle != INVALID_HANDLE_VALUE)
		{
			DWORD bytesWritten;
			if (!WriteFile(fileHandle, memory, fileSize, &bytesWritten, 0) || (fileSize != bytesWritten))
			{
				// TODO: Logging failure to write file
				return false;
			}

			CloseHandle(fileHandle);
		}

		return true;
	}

	PLATFORM_READ_FILE(Win32PlatformReadFile)
	{
		void* result = nullptr;
		*out_Size = 0;

		HANDLE fileHandle = CreateFileA(fileName, GENERIC_READ, FILE_SHARE_READ, nullptr, OPEN_EXISTING, 0, nullptr);
		if (fileHandle != INVALID_HANDLE_VALUE)
		{
			LARGE_INTEGER fileSize;
			if (GetFileSizeEx(fileHandle, &fileSize))
			{
				// TODO: Remove this alloc and pass in the memory needed from the game scratch space
				result = VirtualAlloc(0, fileSize.QuadPart, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
				if (result != nullptr)
				{
					// TODO: Assert(quadpart <= MAX32BUT INT)
					DWORD bytesRead;
					DWORD fileSize32 = (DWORD)fileSize.QuadPart;
					if (!ReadFile(fileHandle, result, fileSize32, &bytesRead, 0) || (fileSize32 != bytesRead))
					{
						// TODO: Logging failure to read file
						VirtualFree(result, 0, MEM_RELEASE);
					}

					*out_Size = bytesRead;
				}
			}

			CloseHandle(fileHandle);
		}

		return result;
	}
}

#endif
