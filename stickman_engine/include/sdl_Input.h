/*
 * 	sdlInput
 *
 *  Created on: May 25, 2011
 *      Author: Bric Rogers
 */

// External includes

#include <iostream>
#include <map>
#include <list>
#include <vector>
#include <SDL_stdinc.h>
#include <SDL_events.h>

// Internal includes
#include "callback.h"


#ifndef SDL_INPUT_H
#define SDL_INPUT_H

namespace stickman_engine
{

	enum mouseMotionState { MOUSE_MOTION_X,		// Only call when a x movement happens func(int xpos, int xdelta)
							MOUSE_MOTION_Y,     // Only call when a y movement happens func(int ypos, int ydelta)
							MOUSE_MOTION_XY     // Call when x or y movement happens func(int xpos, int ypos, int xdelta, int ydelta)
						  };

	struct mouseButtonState
	{
		mouseButtonState( Uint8 button, Uint32 type, bool continuous, Sint32 x, Sint32 y) : _button(button), _type(type), _continuous(continuous), _x(x), _y(y) {}
		mouseButtonState( Uint8 button, Uint32 type, bool continuous) :  _button(button), _type(type), _continuous(continuous), _x(0), _y(0) {}
		mouseButtonState(Uint8 button) :_button(button), _type(SDL_MOUSEBUTTONDOWN), _continuous(false), _x(0), _y(0) { }
		~mouseButtonState() {}

		Uint8 _button;
		Uint32 _type;

		Sint32 _x;				// x value location at time of press
		Sint32 _y;				// y value location at time of press
		bool _continuous;

		bool operator==(const mouseButtonState &other) const 
		{
			return (_type == other._type &&
					_button == other._button);
		}

		bool operator!=(const mouseButtonState &other)
		{
			return !(*this == other);
		}

		//Since the map used the < operator to do comparisons for the find() function (if a < b = false and b < a = false then a = b)
		bool operator<(const mouseButtonState &rhs)const
		{
			// if the buttons are not equal, we can jsut compare by keys
			if(_button != rhs._button)
			{
				if(_button < rhs._button)
					return true;
				else
					return false;
			}
			else // Keys are equal, try to compare by type
			{
				// if the types are not equal, we can just compare by type
				if(_type < rhs._type)
					return true;
				else
					return false;
			} // end else
		}
	};

	struct keyState
	{
		public:
			keyState(SDL_Keycode key, Uint32 type, SDL_Keymod mod, bool continuous) :  _key(key), _type(type), _modifier(mod), _continuous(continuous) {}
			keyState(SDL_Keycode key) :_key(key), _type(SDL_KEYDOWN), _modifier(KMOD_NONE), _continuous(false) {}
			~keyState() {}

			Uint32 _type;				// The state of the keystroke (fire even on keyup or keydown)
			SDL_Keymod _modifier;		// Check for modifiers (num lock, caps lock, etc)
			SDL_Keycode _key;			// The key to check
			bool _continuous;			// If true, will fire the event every frame while the key is in the current state

			bool operator==(const keyState &other) const 
			{
				return (_type == other._type &&
						_modifier == other._modifier &&
					    _key == other._key);
			}

			bool operator!=(const keyState &other)
			{
				return !(*this == other);
			}

			//Since the map used the < operator to do comparisons for the find() function (if a < b = false and b < a = false then a = b)
			bool operator<(const keyState &rhs)const
			{
				// if the keys are not equal, we can jsut compare by keys
				if(_key != rhs._key)
				{
					if(_key < rhs._key)
						return true;
					else
						return false;
				}
				else // Keys are equal, try to compare by type
				{
					// if the types are not equal, we can just compare by type
					if(_type != rhs._type)
					{
						if(_type < rhs._type)
							return true;
						else
							return false;
					}
					else // keys and types are equal, compare by modifier
					{
						if(_modifier < rhs._modifier)
							return true;
						else
							return false;
					} // end else
				} // end else
			} // end func
	};

	
	class sdl_Input
	{
		typedef std::map<keyState, callback0*> KeyMapType;										// Key map (currently only 1 key per keystate)
		typedef std::map<mouseButtonState, callback2<int32_t, int32_t>*> MouseMapType;			// Mouse button map (currently only 1 button per buttonState)
		typedef std::vector<callback2<int32_t, int32_t>*> Mouse1DMotionType;					// Mouse 1D motion map
		typedef std::vector<callback4<int32_t, int32_t, int32_t, int32_t>*> Mouse2DMotionType;	// Mouse 2D motion map
		typedef KeyMapType::iterator ActiveKeyListType;
		typedef MouseMapType::iterator ActiveMouseListType;

		

		public:
			sdl_Input();

			bool init();
			void process();	//process input events
			void cleanup();

			void bindQuitCallback(callback0* cb);
			void bindResizeCallback(callback3<uint32_t, int32_t, int32_t>* cb);
			void bindKeyCallback(keyState ks, callback0 * cb);
			void bindMouseButtonCallback(mouseButtonState ms, callback2<int32_t, int32_t> * cb);
			void bindMouse1DMotionCallback(mouseMotionState mm, callback2<int32_t, int32_t> * cb);
			void bindMouse2DMotionCallback(mouseMotionState mm, callback4<int32_t, int32_t, int32_t, int32_t> * cb);

		protected:

		private:
			callback0* _quitCallback;		// Callback to quit the game
			callback3<uint32_t, int32_t, int32_t> * _resizeCallback;

			KeyMapType _keyMap;
			MouseMapType _mouseButtonMap;

			// using 3 lists instead of a map. There will only ever be 3 options here
			// and we would be doing a map.find() every time the mouse would move
			Mouse1DMotionType _mouseMotionXList;
			Mouse1DMotionType _mouseMotionYList;
			Mouse2DMotionType _mouseMotionXYList;

			// My buffer idea started out good but i am currently iterating through the buffer list twice per frame which sounds pretty bad.
			// though, most of the time it will be nothing or just 1 element in the list. at max it will be about 40 if every single key on the keyboard
			// is pressed at the same time. This method sets me up for doing synchornised input as well as takes care of all keybresses without having
			// to create per key code.
			std::list<ActiveKeyListType> _keyUpEventBuffer;
			std::list<ActiveKeyListType> _keyDownEventBuffer;

			std::list<ActiveMouseListType> _mouseUpEventBuffer;
			std::list<ActiveMouseListType> _mouseDownEventBuffer;;

			void processKeyboardInput(SDL_KeyboardEvent * key);
			void executeBufferedKeyboardEvents();
			void removeFromKeyBuffer(SDL_KeyboardEvent * key);

			void processMouseButtonInput(SDL_MouseButtonEvent * mouseEvent);
			void executeBufferedMouseEvents();
			void removeFromMouseBuffer(SDL_MouseButtonEvent * mouseEvent);

			void processMouseMotionInput(SDL_MouseMotionEvent * motionEvent);
			bool _isFirstFrame;				// I really hate doing this, but i need to skip the first frame because it generates a huge relative
											// reposition
	};
	
}

#endif // SDLINPUT_H
