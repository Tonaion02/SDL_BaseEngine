#include "PrecompiledHeaders.h"

#include "Game.h"





//------------------------------------------------------------------------------------
//Game Class
//------------------------------------------------------------------------------------

//AGGIUNGERE FILE DAL QUALE SI PESCANO OPZIONI DI GIOCO
void Game::init()
{
	SDL_Init(SDL_INIT_EVENTS);

	SDL_Handler::get().init();

	m_isRunning = true;
	m_isFirst = true;
}



void Game::processInput()
{
	SDL_Event event;

	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			m_isRunning = false;
		break;
		}
	}

	const Uint8* state = SDL_GetKeyboardState(NULL);

	if (state[SDL_SCANCODE_ESCAPE])
	{
		m_isRunning = false;
	}
}



void Game::update()
{
	if (m_isFirst)
	{
		m_isFirst = false;

		image = Image("data/images/we.png");

		level = Level("data/levels/level3.tmx");

		pos = { 0.0f, 0.0f };
	}
}



void Game::generateOutput()
{
	Game::get().clearColorScreen(Color(0, 255, 255, 255));

	pos.x += 0.001f;

	level.m_graphicLayer[0][0].blit({ 0, 0 }, (Vector2i)pos, { 900, 720 });
	level.m_graphicLayer[0][1].blit({ 0, 0 }, (Vector2i)pos, { 900, 720 });
	level.m_graphicLayer[1][0].blit({ 0, 0 }, (Vector2i)pos, { 900, 720 });

	SDL_RenderPresent(SDL_Handler::get().getRenderer());
}



void Game::shutdown()
{

}



void Game::runLoop()
{
	while (m_isRunning)
	{
		//Clear Render
		SDL_RenderClear(SDL_Handler::get().getRenderer());
		//Clear Render

		processInput();

		update();
		
		generateOutput();
	}
}



void Game::clearColorScreen(const Color& clearColor)
{
	SDL_SetRenderDrawColor(SDL_Handler::get().getRenderer(), clearColor.r, clearColor.g, clearColor.b, clearColor.a);
}
//------------------------------------------------------------------------------------
//Game Class
//------------------------------------------------------------------------------------