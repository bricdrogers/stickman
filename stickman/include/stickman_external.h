#ifndef STICKMAN_EXTERNAL_H
#define STICKMAN_EXTERNAL_H

#include "stickman.h"
#include "game_memory.h"
#include "game_buffer.h"
#include "Igame_io.h"

// Globals
extern stickman_common::Igame_core * _game_core;
extern bool mInitialize;

#define GAME_INITIALIZE(name) void name(game_memory  *memory, Igame_io *gameIO)			// Initialize Macro
typedef GAME_INITIALIZE(game_initialize);								// Function Pointer

#define GAME_UPDATE_AND_RENDER(name) void name(game_memory *memory, game_buffer *buffer)		// GameUpdateAndRender Macro
typedef GAME_UPDATE_AND_RENDER(game_update_and_render);											// Function Pointer

#endif