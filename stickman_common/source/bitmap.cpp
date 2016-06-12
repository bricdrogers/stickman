#include "bitmap.h"

namespace stickman_common
{
	bitmap::bitmap(void *fileHandle)
	{
		bitmap_header *header = (bitmap_header *)fileHandle;

		// Note, we only will support a bit depth of 32 for now as anything other than 32 is not 4 byte alighted as per
		// the bitmap specification and extra work will need to be done. Until we do that just fail out.
		if (header->BitsPerPixel != 32)
		{
			// TODO: Unsupported bit depth
			return;
		}

		size = header->SizeOfBitmap;
		width = header->Width;
		height = header->Height;
		bitsPerPixel = header->BitsPerPixel;

		pixels = (uint32_t *)((uint8_t *)fileHandle + header->BitmapOffset);

		// Bitmap Pixel format:		AA BB GG RR
		// Stickman Pixel Format:	BB GG RR AA

		//  0xAABBGGRR >> 8 = 0xBBGGRR00
		//  0xAABBGGRR << 24 = 0x000000AA
		//
		//	   0xBBGGRR00
		// OR  0x000000AA
		//  --------------
		//     0xBBGGRRAA
		uint32_t *tempPtr = pixels;
		for (int x = 0; x < width; ++x)
		{
			for (int y = 0; y < height; ++y)
			{
				*tempPtr = (*tempPtr >> 8) | (*tempPtr << 24);
				++tempPtr;
			}
		}
	}
}