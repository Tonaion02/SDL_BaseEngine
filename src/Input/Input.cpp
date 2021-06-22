#include "Input.h"





//------------------------------------------------------------------------------------
//InputHandler Class
//------------------------------------------------------------------------------------
void InputHandler::update()
{
	quit = false;

	SDL_Event event;

	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			quit = true;
			break;
		case SDL_MOUSEBUTTONDOWN:
			//if (event.button.button == SDL_BUTTON_LEFT)
			//{
			//	
			//}
			mouseKeyStates[event.button.button] = true;
			break;
		case SDL_MOUSEBUTTONUP:
			mouseKeyStates[event.button.button] = false;
			break;
		}
	}

	keyStates = SDL_GetKeyboardState(NULL);

	SDL_GetMouseState(&s_pos.x, &s_pos.y);
}



bool InputHandler::isPressed(SDL_Scancode key) const
{
	return keyStates[key];
}



Vector2i InputHandler::getPos() const
{
	return s_pos;
}



bool InputHandler::isQuit() const
{
	return quit;
}



bool InputHandler::isPressed(uint8_t mouseKey) const
{
	//assert for mouseKey;
	return mouseKeyStates[mouseKey];
}
//------------------------------------------------------------------------------------
//InputHandler Class
//------------------------------------------------------------------------------------