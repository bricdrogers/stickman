#ifndef ENGINE_GLOBALS_H
#define ENGINE_GLOBALS_H

// TODO: Precompiled header?

#define PLATFORM_WIN32
//#define PLATFORM_WIN32_SDL

// Remove then define if you want to ship
#define STICKMAN_INTERNAL

// Change the define to STICKMAN_RELEASE for optimized build
#define STICKMAN_DEBUG
//#define STICKMAN_RELEASE

#ifdef STICKMAN_DEBUG
#define ASSERT(expression) if(!(expression)) {*(int *)0 = 0;}
#else
#define ASSERT(expression)
#endif

#endif // ENGINE_GLOBALS_H
