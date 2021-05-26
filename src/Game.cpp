#include "PrecompiledHeaders.h"

#include "Game.h"





//------------------------------------------------------------------------------------
//Game Class
//------------------------------------------------------------------------------------

//AGGIUNGERE FILE DAL QUALE SI PESCANO OPZIONI DI GIOCO
void Game::init()
{
	SDL_Init(SDL_INIT_EVENTS);

	screenDimension = { 900, 720 };
	SDL_Handler::get().init(screenDimension.x, screenDimension.y);

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

		SDL_Log(std::to_string(level.m_tileMaps[0].getCommonTile(3, 1, 0).realType).c_str());

		pos = { 700.0f, 0.0f };
	}

	pos.x -= 0.1f;
}



void Game::generateOutput()
{
	Game::get().clearColorScreen(Color(0, 255, 255, 255));
	
	//Rendering Level
	Vector2i intPosPlayer = (Vector2i)pos;
	Vector2i intTilePosPlayer = { intPosPlayer.x / level.getTileWidth(), intPosPlayer.y / level.getTileHeight() };

	Vector2i nTileToRender = { (((screenDimension.x / level.getTileWidth()) - 1) / 2), (((screenDimension.y / level.getTileHeight()) - 1) / 2) };
	Vector2i backToRender = { intTilePosPlayer.x - nTileToRender.x - 1,intTilePosPlayer.y - nTileToRender.y -1 };
	Vector2i frontToRender = { intTilePosPlayer.x + nTileToRender.x + 1,intTilePosPlayer.y + nTileToRender.y + 1 };

	Vector2i startRectRendering = intPosPlayer - Vector2i(screenDimension.x / 2, screenDimension.y / 2);
	Vector2i endRectRendering = intPosPlayer + Vector2i(screenDimension.x / 2, screenDimension.y / 2);

	//Controll value rendering
	if (startRectRendering.x <= 0)
	{
		startRectRendering.x = 0;
		endRectRendering.x = screenDimension.x;
	}
	else if (endRectRendering.x >= (level.getWidth() * level.getTileWidth()))
	{
		startRectRendering.x = (level.getWidth() * level.getTileWidth()) - screenDimension.x;
		endRectRendering.x = (level.getWidth() * level.getTileWidth());
	}
	if (startRectRendering.y <= 0)
	{
		startRectRendering.y = 0;
		endRectRendering.y = screenDimension.y;
	}
	else if (endRectRendering.y >= (level.getHeight() * level.getTileHeight()))
	{
		startRectRendering.y = (level.getHeight() * level.getTileHeight()) - screenDimension.y;
		endRectRendering.y = (level.getHeight() * level.getTileHeight());
	}
	//Controll value rendering

	//Controll value
	//Momentaneo
	//backToRender.y = 0;
	//frontToRender.y = screenDimension.y / level.getTileHeight();
	if (backToRender.x < 0)
	{
		backToRender.x = 0;
		frontToRender.x = screenDimension.x / level.getTileHeight();
	}

	if (backToRender.y < 0)
	{
		backToRender.y = 0;
		frontToRender.y = screenDimension.y / level.getTileHeight();
	}


	Vector2i posImageLevel = { (level.getWidth() * level.getTileWidth()) - screenDimension.x, 0};
	//Momentaneo
	//Controll value

	Vector2i renderAdj = { intPosPlayer.x - (intTilePosPlayer.x * level.getTileWidth()), intPosPlayer.y - (intTilePosPlayer.y * level.getTileHeight()) };

	for (int i = 0; i < level.m_tileMaps.size(); i++)
	{
		level.m_graphicLayer[i][0].blit({ 0, 0 }, startRectRendering, screenDimension);

		//Rendering UniqueTileLayer
		for (int y = backToRender.y; y < frontToRender.y; y++)
		{
			int rendY = (y * level.getTileHeight()) - startRectRendering.y;
			for (int x = backToRender.x; x < frontToRender.x; x++)
			{
				int rendX = (x * level.getTileWidth()) - startRectRendering.x;
				//Momentaneo
				//image.blit({ rendY, rendX });
				if (level.m_tileMaps[i].getCommonTile(x, y, 0).isUnique())
				{
					int index = level.m_tileMaps[i].m_uniqueTileLayer.m_indexMatrix[y][x];
					level.m_tileMaps[i].m_uniqueTileLayer.m_destructbleTiles[index].getCurrentImage().blit({ rendX, rendY });
				}
				//Momentaneo
			}
		}
		//Rendering UniqueTileLayer

		for (int j = 1; j < level.m_graphicLayer[i].size(); j++)
		{
			level.m_graphicLayer[i][j].blit({ 0, 0 }, startRectRendering, screenDimension);
		}
	}
	//Rendering Level

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