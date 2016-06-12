#ifndef ENGINE_API_H
#define ENGINE_API_H

#include <stdint.h>
#include <string>

namespace stickman_common
{
	struct assembly_info
	{
		std::string exeFilePath;
		std::string dataPath;
	};

	// ***
	// IO
	// ***

	#define PLATFORM_READ_FILE(name) void *name(const char *fileName, int32_t *out_Size)
	typedef PLATFORM_READ_FILE(platform_read_file);

	#define PLATFORM_WRITE_FILE(name) bool name(const char *fileName, uint32_t fileSize, void *memory)		
	typedef PLATFORM_WRITE_FILE(platform_write_file);

	// ***
	// ASSETS
	// ***
	#define LOAD_BITMAP(name) void name (const char *filePath)
	typedef LOAD_BITMAP(load_bitmap);
	struct engine_assetsAPI
	{
		load_bitmap * loadBitmap;
	};

	class engineAPI
	{
	public:
		platform_write_file * writeFile;
		platform_read_file * readFile;
		assembly_info * assemblyInfo;

		engine_assetsAPI engine_assets;
	};
}

#endif // ENGINE_API_H