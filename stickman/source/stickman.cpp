#include "stickman.h"
#include "game_state.h"

namespace stickman_game
{
	using namespace stickman_common;

	stickman::stickman() {}
	stickman::~stickman() {}


	bool stickman::initialize(game_memory *memory, engineAPI *engineAPI)
	{
		// Initialize game state
		game_state *state = memory->getGameState();
		state->test = 100;
		
		// Store the IO class for later use
		_engineAPI = engineAPI;

		// Test Loading
		_testData = _engineAPI->assets->loadBitmap("BitmapTest1920x1080.bmp");

		return true;
	}

	void stickman::update_and_render(game_memory *memory, game_buffer *buffer)
	{
		game_state *state = memory->getGameState();
		int works = state->test;

		// Test Bitmap Draw
		int32_t actualWidth = _testData->width;
		int32_t actualHeight = _testData->height;

		if (_testData->width > buffer->width)
		{
			actualWidth = buffer->width;
		}

		if (_testData->height > buffer->height)
		{
			actualHeight = buffer->height;
		}

		uint8_t *row = (uint8_t*)buffer->memory;
		uint32_t *sourceRow = _testData->pixels + ((_testData->height - 1) * _testData->width);
		for (int y = 0; y < actualHeight; ++y)
		{
			uint32_t *pixel = (uint32_t*)row;
			uint32_t *source = sourceRow;
			for (int x = 0; x < actualWidth; ++x)
			{
				*pixel++ = *source++;
			}
			row += buffer->stride;
			sourceRow -= _testData->width;
		}

		//// test pattern
		//static int xoffset = 0;
		//static int yoffset = 0;

		//uint8_t *row = (uint8_t*)buffer->memory;
		//for (int y = 0; y < buffer->height; ++y)
		//{
		//	uint32_t *pixel = (uint32_t*)row;

		//	for (int x = 0; x < buffer->width; ++x)
		//	{
		//		// BB GG RR xx
		//		uint8_t R = (uint8_t)(x + xoffset);
		//		uint8_t G = (uint8_t)(y + xoffset);
		//		uint8_t B = (uint8_t)(y + yoffset);

		//		*pixel++ = ((R << 16) | (G << 8) | B);
		//	}

		//	row += buffer->stride;
		//}

		//++xoffset;
		//++yoffset;
	}
}