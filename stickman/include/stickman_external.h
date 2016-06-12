#ifndef STICKMAN_EXTERNAL_H
#define STICKMAN_EXTERNAL_H

#include "stickman.h"
#include "game_memory.h"
#include "game_buffer.h"
#include "engineAPI.h"

// Globals
extern stickman_game::stickman* _game;

#define GAME_INITIALIZE(name) bool name(game_memory *memory, engineAPI *engineAPI)			// Initialize Macro
typedef GAME_INITIALIZE(game_initialize);													// Function Pointer

#define GAME_UPDATE_AND_RENDER(name) void name(game_memory *memory, game_buffer *buffer)		// GameUpdateAndRender Macro
typedef GAME_UPDATE_AND_RENDER(game_update_and_render);											// Function Pointer

#endif