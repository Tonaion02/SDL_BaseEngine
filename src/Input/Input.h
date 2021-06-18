#pragma once

#include "PrecompiledHeaders.h"

#include "SDL_scancode.h"
#include "SDL_keyboard.h"





class InputHandler
{
public:
	static InputHandler& get()
	{
		static InputHandler instance;
		return instance;
	}

	void update();
	bool isPressed(SDL_Scancode key);

protected:
	InputHandler() {}

protected:
	const Uint8* keyStates;
};