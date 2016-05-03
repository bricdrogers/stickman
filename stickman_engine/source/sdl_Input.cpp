#if 0

#include "globals.h"

#ifdef  PLATFORM_WIN32_SDL

#include <SDL.h>	// Simple DirectMedia Layer
#include "sdl_Input.h"

namespace stickman_engine
{
	sdl_Input::sdl_Input()
	{
		_quitCallback = nullptr;
		_resizeCallback = nullptr;
	}

	void sdl_Input::cleanup()
	{
		// Clean up the keymap
		_keyMap.clear();


		if (_quitCallback != nullptr)
		{
			delete _quitCallback;
			_quitCallback = nullptr;
		}

		if (_resizeCallback != nullptr)
		{
			delete _resizeCallback;
			_resizeCallback = nullptr;
		}
	}

	bool sdl_Input::init()
	{
		_isFirstFrame = true;
		SDL_SetRelativeMouseMode(SDL_FALSE);
		SDL_ShowCursor(SDL_DISABLE);

		return true;
	}

	void sdl_Input::process()
	{
		SDL_Event Event;
		
		while(SDL_PollEvent(&Event))
		{
			switch(Event.type)
			{
				case SDL_QUIT:
					_quitCallback->execute();
					break;
		
				case SDL_WINDOWEVENT_RESIZED:
					_resizeCallback->execute(Event.window.windowID, Event.window.data1, Event.window.data2);
					break;
		
				case SDL_MOUSEMOTION:
		
					if(_isFirstFrame)
						break;
		
		
					processMouseMotionInput(&Event.motion);
					break;
		
				case SDL_MOUSEBUTTONUP:
				case SDL_MOUSEBUTTONDOWN:
					removeFromMouseBuffer(&Event.button);
					processMouseButtonInput(&Event.button);
					break;
		
				case SDL_KEYUP:
				case SDL_KEYDOWN:
					removeFromKeyBuffer(&Event.key);			// Clean up the keyboard buffer
					processKeyboardInput(&Event.key);		// Process the keyboard input into the buffer
					break;
		
				default:
					break;
		
			} // end switch
		} // end while	

		// We need to skip the first frame
		if (_isFirstFrame)
		{
			_isFirstFrame = false;
			return;
		}

		executeBufferedKeyboardEvents();		// Execute the keyboard input callback functions
		executeBufferedMouseEvents();			// Execute the mouse input callback functions

	} // end process()

	void sdl_Input::bindQuitCallback(callback0* cb) { _quitCallback = cb; }
	void sdl_Input::bindKeyCallback(keyState ks, callback0 * cb) { _keyMap[ks] = cb; }
	void sdl_Input::bindMouseButtonCallback(mouseButtonState ms, callback2<int32_t, int32_t> * cb) { _mouseButtonMap[ms] = cb; }
	void sdl_Input::bindResizeCallback(callback3<uint32_t, int32_t, int32_t>* cb){ _resizeCallback = cb; }

	void sdl_Input::bindMouse1DMotionCallback(mouseMotionState mm, callback2<int32_t, int32_t> * cb)
	{
		switch (mm)
		{
			case mouseMotionState::MOUSE_MOTION_X:

				_mouseMotionXList.push_back(cb);
				break;

			case mouseMotionState::MOUSE_MOTION_Y:

				_mouseMotionYList.push_back(cb);
				break;
		}
	}

	void sdl_Input::bindMouse2DMotionCallback(mouseMotionState mm, callback4<int32_t, int32_t, int32_t, int32_t> * cb)
	{
		switch(mm)
		{
			case mouseMotionState::MOUSE_MOTION_XY:

				_mouseMotionXYList.push_back(cb);
				break;
		}
	}

	void sdl_Input::processMouseMotionInput(SDL_MouseMotionEvent * motionEvent)
	{
		// check to see if we have relative changes

		if(motionEvent->xrel != 0 || motionEvent->yrel != 0)
		{
			// if both position delta's are greater than zero, we know for sure thay we have to trigger
			// the XY event
			Mouse2DMotionType::iterator mm_iter = _mouseMotionXYList.begin();
			
			while(mm_iter != _mouseMotionXYList.end())
			{
				(*mm_iter)->execute(motionEvent->x, motionEvent->y, motionEvent->xrel, motionEvent->yrel);
				++mm_iter;
			}

			// Now check for x
			if(motionEvent->xrel != 0)
			{
				Mouse1DMotionType::iterator mmx_iter = _mouseMotionXList.begin();

				while(mmx_iter != _mouseMotionXList.end())
				{
					(*mmx_iter)->execute(motionEvent->x, motionEvent->xrel);
					++mmx_iter;
				}
			}

			if(motionEvent->yrel != 0)
			{
				Mouse1DMotionType::iterator mmy_iter = _mouseMotionYList.begin();

				while(mmy_iter != _mouseMotionYList.end())
				{
					(*mmy_iter)->execute(motionEvent->y, motionEvent->yrel);
					++mmy_iter;
				}
			}
		}
	}

	void sdl_Input::processMouseButtonInput(SDL_MouseButtonEvent * mouseEvent)
	{
		// Get the button (the boolean does not matter, it is not part of the search)
		mouseButtonState ms = mouseButtonState(mouseEvent->button, mouseEvent->type, false, mouseEvent->x, mouseEvent->y);
		
		MouseMapType::iterator mm_iter = _mouseButtonMap.find(ms);

		if(mm_iter != _mouseButtonMap.end())
		{
			// First check to see if we need to add the input to a buffer (if we are not looking for a continuous key)
			if(mm_iter->first._continuous == false)
			{
				mm_iter->second->execute(mouseEvent->x, mouseEvent->y);		// Execute the callback and then we are done
				return;
			}

			// If we find a match, add the event to the buffer
			if(ms._type == SDL_MOUSEBUTTONDOWN)
			{
				_mouseDownEventBuffer.push_front(mm_iter);
			}
			else if(ms._type == SDL_MOUSEBUTTONUP)
			{
				_mouseUpEventBuffer.push_front(mm_iter);
			}
		}
		
	}

	void sdl_Input::processKeyboardInput(SDL_KeyboardEvent * key)
	{
		// Get the key (the boolean does not matter, it is not part of the search)
		keyState ks = keyState(key->keysym.sym, key->type, (SDL_Keymod)key->keysym.mod, false);

		KeyMapType::iterator km_iter = _keyMap.find(ks);

		if(km_iter != _keyMap.end())
		{
			if(km_iter->first._continuous == false)
			{
				km_iter->second->execute();
				return;
			}

			// If we find a match, add the event to the buffer
			if(ks._type == SDL_KEYDOWN)
			{
				_keyDownEventBuffer.push_front(km_iter);
			}
			else if(ks._type == SDL_KEYUP)
			{
				_keyUpEventBuffer.push_front(km_iter);
			}
		}

		// If it is not in the key map. we just ignore the keypress
	}


	void sdl_Input::executeBufferedMouseEvents()
	{
		// Execute keydown event buffers
		if(!_mouseDownEventBuffer.empty())
		{
			// loop though the keyDown event list (use a while loop so we can remove elements withough having to walk the list again)
			std::list<ActiveMouseListType>::iterator md_iter = _mouseDownEventBuffer.begin();
	
			while(md_iter != _mouseDownEventBuffer.end())
			{
				//execute the event
				if((*md_iter)->second != 0) // make sure the callback function exists
				{
					(*md_iter)->second->execute((*md_iter)->first._x, (*md_iter)->first._y);
				}

				// Now we need to check if we can remove the event from the list (if it is not continuous)
				if(!(*md_iter)->first._continuous)
				{
					// This will delete the kd_iter event from the list
					// and return a iterator to the next element (essentialy iterating it)
					md_iter = _mouseDownEventBuffer.erase(md_iter);
				}
				else
				{
					// if we dont remove it, we need to increment the iterator
					++md_iter;
				}

			} // end while
		} // end if

		// Execute keyup event buffers
		if(!_mouseUpEventBuffer.empty())
		{
			// loop though the keyDown event list (use a while loop so we can remove elements withough having to walk the list again)
			std::list<ActiveMouseListType>::iterator mu_iter = _mouseUpEventBuffer.begin();
	
			while(mu_iter != _mouseUpEventBuffer.end())
			{
				//execute the event
				if((*mu_iter)->second != 0) // make sure the callback function exists
				{
					(*mu_iter)->second->execute((*mu_iter)->first._x, (*mu_iter)->first._y);
				}

				// Now we need to check if we can remove the event from the list (if it is not continuous)
				if(!(*mu_iter)->first._continuous)
				{
					// This will delete the kd_iter event from the list
					// and return a iterator to the next element (essentialy iterating it)
					mu_iter = _mouseUpEventBuffer.erase(mu_iter);
				}
				else
				{
					// if we dont remove it, we need to increment the iterator
					++mu_iter;
				}

			} // end while
		} // end if
	}

	void sdl_Input::executeBufferedKeyboardEvents()
	{
		// Execute keydown event buffers
		if(!_keyDownEventBuffer.empty())
		{
			// loop though the keyDown event list (use a while loop so we can remove elements withough having to walk the list again)
			std::list<ActiveKeyListType>::iterator kd_iter = _keyDownEventBuffer.begin();
	
			while(kd_iter != _keyDownEventBuffer.end())
			{
				//execute the event
				if((*kd_iter)->second != 0) // make sure the callback function exists
				{
					(*kd_iter)->second->execute();
				}

				// Now we need to check if we can remove the event from the list (if it is not continuous)
				if(!(*kd_iter)->first._continuous)
				{
					// This will delete the kd_iter event from the list
					// and return a iterator to the next element (essentialy iterating it)
					kd_iter = _keyDownEventBuffer.erase(kd_iter);
				}
				else
				{
					// if we dont remove it, we need to increment the iterator
					++kd_iter;
				}

			} // end while
		} // end if


		// Execute keyup event buffers
		if(!_keyUpEventBuffer.empty())
		{
			// loop though the keyUp event list (use a while loop so we can remove elements withough having to walk the list again)
			std::list<ActiveKeyListType>::iterator ku_iter = _keyUpEventBuffer.begin();
	
			while(ku_iter != _keyUpEventBuffer.end())
			{
				//execute the event
				if((*ku_iter)->second != 0) // make sure the callback function exists
				{
					(*ku_iter)->second->execute();
				}

				// Now we need to check if we can remove the event from the list (if it is not continuous)
				if(!(*ku_iter)->first._continuous)
				{
					// This will delete the ku_iter event from the list
					// and return a iterator to the next element (essentialy iterating it)
					ku_iter = _keyUpEventBuffer.erase(ku_iter);
				}
				else
				{
					// if we dont remove it, we need to increment the iterator
					++ku_iter;
				}

			} // end while
		} // end if


	} // end func

	void sdl_Input::removeFromMouseBuffer(SDL_MouseButtonEvent * mouseEvent)
	{
		// we have a mouse up event, we need to remove the continuous keydown event key
		if(mouseEvent->type == SDL_MOUSEBUTTONUP)
		{
			if(!_mouseDownEventBuffer.empty())
			{
				mouseButtonState buttonUp = mouseButtonState(mouseEvent->button, SDL_MOUSEBUTTONDOWN, true);

				// Note:
				// kd_iter->first is of type <KeyState, IfCallback*>
				std::list<ActiveMouseListType>::iterator md_iter = _mouseDownEventBuffer.begin();	// get a iterator to the beginning of the list

				while(md_iter != _mouseDownEventBuffer.end())
				{
					// if the current key state has a match within the buffer list (with the keyup/keydown flipped) we need to remove it from the buffers
					if((*md_iter)->first == buttonUp)
					{
						// This will delete the kd_iter event from the list
						// and return a iterator to the next element (essentialy iterating it)
						md_iter = _mouseDownEventBuffer.erase(md_iter);

						// early out
						break;
					}
					else
					{
						// if we dont remove it, we need to increment the iterator
						++md_iter;
					} // end else
				} // end while
			} // end if
		} 
		else if(mouseEvent->type == SDL_MOUSEBUTTONDOWN)
		{
			if(!_mouseUpEventBuffer.empty())
			{
				mouseButtonState buttonDown = mouseButtonState(mouseEvent->button, SDL_MOUSEBUTTONUP, true);

				// Note:
				// kd_iter->first is of type <KeyState, IfCallback*>
				std::list<ActiveMouseListType>::iterator mu_iter = _mouseUpEventBuffer.begin();	// get a iterator to the beginning of the list

				while(mu_iter != _mouseUpEventBuffer.end())
				{
					// if the current key state has a match within the buffer list (with the keyup/keydown flipped) we need to remove it from the buffers
					if((*mu_iter)->first == buttonDown)
					{
						// This will delete the kd_iter event from the list
						// and return a iterator to the next element (essentialy iterating it)
						mu_iter = _mouseUpEventBuffer.erase(mu_iter);

						// early out
						break;
					}
					else
					{
						// if we dont remove it, we need to increment the iterator
						++mu_iter;
					} // end elses
				} // end while
			} // end if
		} // end if keyup
	}

	void sdl_Input::removeFromKeyBuffer(SDL_KeyboardEvent * key)
	{
		// we have a key up event, we need to remove the continuous keydown event key
		if(key->type == SDL_KEYUP)
		{

			if(!_keyDownEventBuffer.empty())
			{
				keyState upKey = keyState(key->keysym.sym, SDL_KEYDOWN, (SDL_Keymod)key->keysym.mod, true);

				// Note:
				// kd_iter->first is of type <KeyState, IfCallback*>
				std::list<ActiveKeyListType>::iterator kd_iter = _keyDownEventBuffer.begin();	// get a iterator to the beginning of the list

				while(kd_iter != _keyDownEventBuffer.end())
				{
					// if the current key state has a match within the buffer list (with the keyup/keydown flipped) we need to remove it from the buffers
					if((*kd_iter)->first == upKey)
					{
						// This will delete the kd_iter event from the list
						// and return a iterator to the next element (essentialy iterating it)
						kd_iter = _keyDownEventBuffer.erase(kd_iter);

						// early out
						break;				
					}
					else
					{
						// if we dont remove it, we need to increment the iterator
						++kd_iter;
					} // end else
				} // end while
			} // end if
		} 
		else if(key->type == SDL_KEYDOWN)
		{
			if(!_keyUpEventBuffer.empty())
			{
				keyState downKey = keyState(key->keysym.sym, SDL_KEYUP, (SDL_Keymod)key->keysym.mod, true);

				// Note:
				// kd_iter->first is of type <KeyState, IfCallback*>
				std::list<ActiveKeyListType>::iterator ku_iter = _keyUpEventBuffer.begin();	// get a iterator to the beginning of the list

				while(ku_iter != _keyUpEventBuffer.end())
				{
					// if the current key state has a match within the buffer list (with the keyup/keydown flipped) we need to remove it from the buffers
					if((*ku_iter)->first == downKey)
					{
						// This will delete the kd_iter event from the list
						// and return a iterator to the next element (essentialy iterating it)
						ku_iter = _keyUpEventBuffer.erase(ku_iter);

						// early out
						break;
					}
					else
					{
						// if we dont remove it, we need to increment the iterator
						++ku_iter;
					} // end elses
				} // end while
			} // end if
		} // end if keyup
	} // end func

}// end stickman namespace

#endif //  PLATFORM_WIN32_SDL

#endif