#pragma once

#include "PrecompiledHeaders.h"

#define SDL_MAIN_HANDLED
#include "SDL.h"
#include "SDL_image.h"





class SDL_Handler
{
public:
	static SDL_Handler& get()
	{
		static SDL_Handler instance;
		return instance;
	}

	void init(int resolutionX=900, int resolutionY=720);

	SDL_Window* getWindow();
	SDL_Renderer* getRenderer();

protected:
	SDL_Handler() {}

	SDL_Window* m_window;
	SDL_Renderer* m_renderer;
};