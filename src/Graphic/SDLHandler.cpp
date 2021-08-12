#include "SDLHandler.h"





//------------------------------------------------------------------------------------
//SDL_Handler Class
//------------------------------------------------------------------------------------
void SDL_Handler::init(const Vector2i& dimension)
{
	SDL_Init(SDL_INIT_VIDEO);
	
	if (TTF_Init() >= 0)
	{
		SDL_Log("Successfull initializing TTF System");
	}
	else
	{
		std::string errorMessage = "Error initializing TTF System" + std::string(TTF_GetError());
		SDL_Log(errorMessage.c_str());
	}
	
	m_window = SDL_CreateWindow("title", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, dimension.x, dimension.y, SDL_WINDOW_SHOWN);
	m_renderer = SDL_CreateRenderer(m_window, -1, 0);
}



SDL_Renderer* SDL_Handler::getRenderer()
{
	return m_renderer;
}



SDL_Window* SDL_Handler::getWindow()
{
	return m_window;
}
//------------------------------------------------------------------------------------
//SDL_Handler Class
//------------------------------------------------------------------------------------