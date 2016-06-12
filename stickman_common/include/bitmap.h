#ifndef BITMAP_H
#define BITMAP_H

#include <stdint.h>

namespace stickman_common
{
	// TODO: bitmap cleanup

	class bitmap
	{
	public:
		bitmap(void *fileHandle);

		uint32_t size;				/* Size of bitmap in bytes */
		int32_t width;				/* Image width in pixels */
		int32_t height;				/* Image height in pixels */
		uint16_t bitsPerPixel;		/* Number of bits per pixel */

		// Pixel format: AA BB GG RR -> bottom up
		uint32_t *pixels;		    /* Pixel buffer for the bitmap */

	private:
		// bitmap file format
		// http://www.fileformat.info/format/bmp/egff.htm

		// A note on pragma pack
		// the compiler does not have to create a data structure in the format
		// your give it. It can byte align things where it sees fit. If we want to be able
		// to cold cast things, we will have to tell the compiler to not try to byte align
		// anythign in the structure

#pragma pack(push, 1)
		struct bitmap_header
		{
			uint16_t FileType;			/* File type, always 4D42h ("BM") */
			uint32_t FileSize;			/* Size of the file in bytes */
			uint16_t Reserved1;			/* Always 0 */
			uint16_t Reserved2;			/* Always 0 */
			uint32_t BitmapOffset;		/* Starting position of image data in bytes */
			uint32_t Size;				/* Size of this header in bytes */
			int32_t Width;				/* Image width in pixels */
			int32_t Height;				/* Image height in pixels */
			uint16_t Planes;			/* Number of color planes */
			uint16_t BitsPerPixel;		/* Number of bits per pixel */
			uint32_t Compression;		/* Compression methods used */
			uint32_t SizeOfBitmap;		/* Size of bitmap in bytes */
			int32_t HorzResolution;		/* Horizontal resolution in pixels per meter */
			int32_t VertResolution;		/* Vertical resolution in pixels per meter */
			uint32_t ColorsUsed;		/* Number of colors in the image */
			uint32_t ColorsImportant;	/* Minimum number of important colors */

										/* Fields added for Windows 4.x follow this line */

			uint32_t RedMask;			/* Mask identifying bits of red component */
			uint32_t GreenMask;			/* Mask identifying bits of green component */
			uint32_t BlueMask;			/* Mask identifying bits of blue component */
			uint32_t AlphaMask;			/* Mask identifying bits of alpha component */
			uint32_t CSType;			/* Color space type */
			int32_t RedX;				/* X coordinate of red endpoint */
			int32_t RedY;				/* Y coordinate of red endpoint */
			int32_t RedZ;				/* Z coordinate of red endpoint */
			int32_t GreenX;				/* X coordinate of green endpoint */
			int32_t GreenY;				/* Y coordinate of green endpoint */
			int32_t GreenZ;				/* Z coordinate of green endpoint */
			int32_t BlueX;				/* X coordinate of blue endpoint */
			int32_t BlueY;				/* Y coordinate of blue endpoint */
			int32_t BlueZ;				/* Z coordinate of blue endpoint */
			uint32_t GammaRed;			/* Gamma red coordinate scale value */
			uint32_t GammaGreen;		/* Gamma green coordinate scale value */
			uint32_t GammaBlue;			/* Gamma blue coordinate scale value */
		};
#pragma pack(pop)
	};
}

#endif // BITMAP_H
