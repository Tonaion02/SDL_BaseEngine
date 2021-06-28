#pragma once

#include "PrecompiledHeaders.h"

#include "SDL_scancode.h"
#include "SDL_keyboard.h"

#include "SDL_mouse.h"

#include "SDL_events.h"

#include "Math/Vector.h"





class InputHandler
{
public:
	static InputHandler& get()
	{
		static InputHandler instance;
		return instance;
	}

	void update();
	bool isPressed(SDL_Scancode key) const;
	bool isPressed(uint8_t mouseKey) const;
	Vector2i getPos() const;
	bool isQuit() const;

protected:
	InputHandler() {}

protected:
	const Uint8* keyStates;
	std::array<bool, 5> mouseKeyStates;
	bool quit = false;

	Vector2i s_pos;
};