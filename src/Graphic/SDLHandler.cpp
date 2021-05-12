#include "SDLHandler.h"





//------------------------------------------------------------------------------------
//SDL_Handler Class
//------------------------------------------------------------------------------------
void SDL_Handler::init(int resolutionX, int resolutionY)
{
	SDL_Init(SDL_INIT_VIDEO);
	m_window = SDL_CreateWindow("title", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, resolutionX, resolutionY, SDL_WINDOW_SHOWN);
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