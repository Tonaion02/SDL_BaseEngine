#pragma once

#include "PrecompiledHeaders.h"

#include "Math/Vector.h"

#define SDL_MAIN_HANDLED
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"





class SDL_Handler
{
public:
	static SDL_Handler& get()
	{
		static SDL_Handler instance;
		return instance;
	}

	void init(const Vector2i& dimension);

	SDL_Window* getWindow();
	SDL_Renderer* getRenderer();

protected:
	SDL_Handler() {}

	SDL_Window* m_window;
	SDL_Renderer* m_renderer;
};