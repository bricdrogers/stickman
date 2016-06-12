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

		//// Test Loading
		int32_t outsize;
		std::string testPath = _engineAPI->assemblyInfo->dataPath + "BitmapTest1920x1080.bmp";
		void * testPtr = _engineAPI->readFile(testPath.c_str(), &outsize);

		return true;
	}

	void stickman::update_and_render(game_memory *memory, game_buffer *buffer)
	{
		game_state *state = memory->getGameState();
		int works = state->test;

		// write to buffer
		static int xoffset = 0;
		static int yoffset = 0;

		uint8_t *row = (uint8_t*)buffer->memory;
		for (int y = 0; y < buffer->height; ++y)
		{
			uint32_t *pixel = (uint32_t*)row;

			for (int x = 0; x < buffer->width; ++x)
			{
				// BB GG RR xx
				uint8_t R = (uint8_t)(x + xoffset);
				uint8_t G = (uint8_t)(y + xoffset);
				uint8_t B = (uint8_t)(y + yoffset);

				*pixel++ = ((R << 16) | (G << 8) | B);
			}

			row += buffer->stride;
		}

		++xoffset;
		++yoffset;
	}
}