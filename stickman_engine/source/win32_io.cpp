// External includes
#include <Windows.h>
#include <stdint.h>

// Internal Includes
#include "win32_io.h"

namespace stickman_engine
{
	void *win32_io::readFile(char *fileName, int32_t *out_Size)
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

	bool win32_io::writeFile(char *fileName, uint32_t fileSize, void *memory)
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
}