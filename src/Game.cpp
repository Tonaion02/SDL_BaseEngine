#include "PrecompiledHeaders.h"

#include "Game.h"





// Delta time is the difference in ticks from last fra
//AGGIUNGERE SISTEMA DI FILTRAGGIO E STOCKAGGIO DEGLI INPUT
//AGGIUNGERE FILE DAL QUALE SI PESCANO PROGRESSI DI GIOCO(SAVESLOT)
//AGGIUNGERE I VARI TIPI DI TILE DIFFERENTI DECISI FINO AD ORA
//AGGIUNGERE ANIMAZIONI
//AGGIUNGERE CLASSE PLAYER(forse è necessario aggiungere prima le entità in generale)
//AGGIUNGERE CLASSE PER GESTIRE GLI STATI IN GAME

//TEST NECESSARI:
//-Aggiungere tile modificati un pò in giro
//-Far sostituire automaticamente gli UniqueTile Type nel first layer del TileLayer
//-creare funzione che permette di andare a modificare gli fps(importante controllare se è vsync e nel caso non farlo aggiornare)
//

//------------------------------------------------------------------------------------
//Game Class                                                                           
//------------------------------------------------------------------------------------
void Game::updateDeltaTime()
{
	//Update DeltaTime and TicksCount
	s_deltaTime = (SDL_GetTicks() - s_ticksCount) / 1000.0f;
	//SDL_Log(std::to_string(s_deltaTime).c_str());
	s_ticksCount = SDL_GetTicks();
	//Update DeltaTime and TicksCount



	//Clamp Max value of deltaTime
	//TODO: parametrizzare questo valore massimo
	if (s_deltaTime > 0.05f)
	{
		s_deltaTime = 0.05f;
	}
	//Clamp Max value of deltaTime
}



void Game::sleep()
{
	if (Options::get().isVsync())
	{
		while (!SDL_TICKS_PASSED(SDL_GetTicks(), s_ticksCount + 16));
	}
}



void Game::clearColorScreen(const Color& clearColor)
{
	SDL_SetRenderDrawColor(SDL_Handler::get().getRenderer(), clearColor.r, clearColor.g, clearColor.b, clearColor.a);
}



void Game::renderGraphics()
{
	SDL_RenderPresent(SDL_Handler::get().getRenderer());
}





void Game::first()
{
	if (m_isFirst)
	{
		m_isFirst = false;

		World::get().loadLevel("data/levels/Level5.tmx");
		currentLevel = World::get().getLevel(World::get().getIndexLevel("data/levels/Level5.tmx"));

		entity.pos = Vector2i( 1.0f, 0.0f );
		entity.posImage = { entity.pos.x * currentLevel.getTileWidth(), entity.pos.y * currentLevel.getTileHeight() };
		entity.z = 0;

		statusHandler.addStatus(GamePhase(GamePhase::Phase::Exploring));

		statusHandler.getStatus(statusHandler.searchStatus(GamePhase(GamePhase::Phase::Exploring))).status = GamePhase::StatusGamePhase::On;

		TileSet tileSet = TileSet("data/tileset/playerTileSet16.tsx", 0, false);
		entityTileSetHandler.addTileSet(tileSet);

		entity.tileDimension = { currentLevel.getTileWidth(), currentLevel.getTileHeight() };
		
		entity.animations.push_back(std::vector<std::vector<DinamicAnimation>>(0));
		entity.animations.push_back(std::vector<std::vector<DinamicAnimation>>(0));

		for (int i = 0; i < entity.animations.size(); i++)
		{
			for (int j = 0; j < 2; j++)
			{
				entity.animations[i].push_back(std::vector<DinamicAnimation>(0));
			}
		}

		entity.animations[0][0].push_back(DinamicAnimation({ 0, 0 }, "player.tsx", 0.2f, entity.pos, 0.2f, { 0, -currentLevel.getTileHeight() }));
		entity.animations[0][0].push_back(DinamicAnimation({ 0, 0 }, "player.tsx", 0.2f, entity.pos, 0.2f, { 0, currentLevel.getTileHeight() }));
		entity.animations[0][0].push_back(DinamicAnimation({ 0, 0 }, "player.tsx", 0.2f, entity.pos, 0.2f, { currentLevel.getTileWidth(), 0 }));
		entity.animations[0][0].push_back(DinamicAnimation({ 0, 0 }, "player.tsx", 0.2f, entity.pos, 0.2f, { -currentLevel.getTileWidth(), 0 }));

		entity.idStaticImage.push_back(0);
		entity.idStaticImage.push_back(0);
		entity.idStaticImage.push_back(0);
		entity.idStaticImage.push_back(0);

		s_ticksCount = 0;

		//Init Camera

		Camera::get().init({ currentLevel.getTileWidth(), currentLevel.getTileHeight() }, { currentLevel.getWidth(), currentLevel.getHeight() });
		//Init Camera
	}
}



void Game::init()
{
	SDL_Init(SDL_INIT_EVENTS);

	Options::get().Init("data/options/options.tx");
	SDL_Handler::get().init(Options::get().getScreenDimension());
	screenDimension = Options::get().getScreenDimension();

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

	InputHandler::get().update();

	if (InputHandler::get().isPressed(SDL_SCANCODE_ESCAPE))
	{
		m_isRunning = false;
	}

	if (InputHandler::get().isPressed(SDL_SCANCODE_W))
	{
		SDL_Log("w");
	}
}



void Game::update()
{
	first();

	for (int indexPhase = statusHandler.getSize()-1; indexPhase >= 0; indexPhase--)
	{
		GamePhase actualPhase = statusHandler.getStatus(indexPhase);
		GamePhase::StatusGamePhase statusActualPhase = statusHandler.getStatus(indexPhase).status;

		//Exploring
		if (actualPhase.phase == GamePhase::Phase::Exploring)
		{
			if (entity.statusMovement == StatusMovement::Lock)
			{
				if (InputHandler::get().isPressed(SDL_SCANCODE_W))
				{
					entity.startMove(Direction::Up);
				}
				else if (InputHandler::get().isPressed(SDL_SCANCODE_S))
				{
					entity.startMove(Direction::Down);
				}
				else if (InputHandler::get().isPressed(SDL_SCANCODE_D))
				{
					entity.startMove(Direction::Right);
				}
				else if (InputHandler::get().isPressed(SDL_SCANCODE_A))
				{
					entity.startMove(Direction::Left);
				}
			}

			entity.update(s_deltaTime, currentLevel.m_tileMaps[entity.z]);
			Camera::get().updatePos(entity.posImage);
		}
		//Exploring



		//Battling
		//Battling



		//Dialoging
		//Dialoging
	}
}



void Game::generateOutput()
{
	for (int indexPhase = statusHandler.getSize() - 1; indexPhase >= 0; indexPhase--)
	{
		GamePhase actualPhase = statusHandler.getStatus(indexPhase);

		//Exploring
		if (actualPhase.phase == GamePhase::Phase::Exploring)
		{
			//Clear Screen
			Game::get().clearColorScreen(Color(0, 255, 255, 255));
			//Clear Screen




			////Rendering Level
			//Vector2i intPosPlayer = (Vector2i)pos;
			//Vector2i intTilePosPlayer = { intPosPlayer.x / currentLevel.getTileWidth(), intPosPlayer.y / currentLevel.getTileHeight() };

			//Vector2i nTileToRender = { (((screenDimension.x / currentLevel.getTileWidth()) - 1) / 2), (((screenDimension.y / currentLevel.getTileHeight()) - 1) / 2) };
			//Vector2i backToRender = { intTilePosPlayer.x - nTileToRender.x - 2,intTilePosPlayer.y - nTileToRender.y - 2 };
			//Vector2i frontToRender = { intTilePosPlayer.x + nTileToRender.x + 2,intTilePosPlayer.y + nTileToRender.y + 2 };

			//Vector2i startRectRendering = intPosPlayer - Vector2i(screenDimension.x / 2, screenDimension.y / 2);
			//Vector2i endRectRendering = intPosPlayer + Vector2i(screenDimension.x / 2, screenDimension.y / 2);

			////Controll value rendering
			//if (startRectRendering.x <= 0)
			//{
			//	startRectRendering.x = 0;
			//	endRectRendering.x = screenDimension.x;
			//}
			//else if (endRectRendering.x >= (currentLevel.getWidth() * currentLevel.getTileWidth()))
			//{
			//	startRectRendering.x = (currentLevel.getWidth() * currentLevel.getTileWidth()) - screenDimension.x;
			//	endRectRendering.x = (currentLevel.getWidth() * currentLevel.getTileWidth());
			//}
			//if (startRectRendering.y <= 0)
			//{
			//	startRectRendering.y = 0;
			//	endRectRendering.y = screenDimension.y;
			//}
			//else if (endRectRendering.y >= (currentLevel.getHeight() * currentLevel.getTileHeight()))
			//{
			//	startRectRendering.y = (currentLevel.getHeight() * currentLevel.getTileHeight()) - screenDimension.y;
			//	endRectRendering.y = (currentLevel.getHeight() * currentLevel.getTileHeight());
			//}
			////Controll value rendering

			////Controll value
			//if (backToRender.x < 0)
			//{
			//	backToRender.x = 0;
			//	frontToRender.x = screenDimension.x / currentLevel.getTileWidth();
			//}

			//if (backToRender.y < 0)
			//{
			//	backToRender.y = 0;
			//	frontToRender.y = screenDimension.y / currentLevel.getTileHeight();
			//}

			//if (frontToRender.x > currentLevel.getWidth())
			//{
			//	frontToRender.x = currentLevel.getWidth();
			//	backToRender.x = currentLevel.getWidth() - screenDimension.x / currentLevel.getTileWidth();
			//}

			//if (frontToRender.y > currentLevel.getHeight())
			//{
			//	frontToRender.y = currentLevel.getHeight();
			//	backToRender.y = currentLevel.getHeight() - screenDimension.y / currentLevel.getTileHeight();
			//}
			////Controll value

			//Vector2i renderAdj = { intPosPlayer.x - (intTilePosPlayer.x * currentLevel.getTileWidth()), intPosPlayer.y - (intTilePosPlayer.y * currentLevel.getTileHeight()) };

			//Rendering currentLevel
			for (int i = 0; i < currentLevel.m_tileMaps.size(); i++)
			{
				//Rendering First TileLayer
				currentLevel.m_graphicLayer[i][0].blit({ 0, 0 }, Camera::get().getStartRectRendering(), screenDimension);
				//Rendering First TileLayer



				//Rendering UniqueTileLayer
				for (int y = Camera::get().getBackToRender().y; y < Camera::get().getFrontToRender().y; y++)
				{
					int rendY = (y * currentLevel.getTileHeight()) - Camera::get().getStartRectRendering().y;
					for (int x = Camera::get().getBackToRender().x; x < Camera::get().getFrontToRender().x; x++)
					{
						int rendX = (x * currentLevel.getTileWidth()) - Camera::get().getStartRectRendering().x;
						//Momentaneo
						//Verify if is unique a CommonTile
						RealType realType = currentLevel.m_tileMaps[i].getCommonTile(x, y, 0).realType;
						if (currentLevel.m_tileMaps[i].getCommonTile(x, y, 0).isUnique())
						{
							int index = currentLevel.m_tileMaps[i].m_uniqueTileLayer.m_indexMatrix[y][x];
							//Select the type of UniqueTile
							switch (realType)
							{
							case NoneTileRealType:
								break;
							case Void:
								break;
							case Graphic:
								break;
							case Ground:
								break;
							case Obstacle:
								break;
							case Sea:
								break;
							case Grass:
								break;
							case Destructble:
								currentLevel.m_tileSetHandler.blitImageTile(currentLevel.m_tileMaps[i].m_uniqueTileLayer.m_destructbleTiles[index].getCurrentImage(),
									currentLevel.m_tileMaps[i].m_uniqueTileLayer.m_destructbleTiles[index].nameTileset,
									{ rendX, rendY });
								break;
							case Chest:
								break;
							case Openable:
								break;
							default:
								break;
							}
							//Select the type of UniqueTile
						}
						//Verify if is unique a CommonTile
						//Momentaneo
					}
				}
				//Rendering UniqueTileLayer

				//Render Player
				if (entity.z == i)
				{
					//image.blit(entity.pos);
					entityTileSetHandler.blitImageTile(entity.getIdImage(), Camera::get().getPlayerPos(Camera::get().getStartRectRendering()));
					//currentLevel.m_tileSetHandler.blitImageTile(entity.getIdImage(), "player.tsx", entity.posImage)
				}
				//Render Player

				//Rendering Other TileLayer
				for (int j = 1; j < currentLevel.m_graphicLayer[i].size(); j++)
				{
					currentLevel.m_graphicLayer[i][j].blit({ 0, 0 }, Camera::get().getStartRectRendering(), screenDimension);
				}
				//Rendering Other TileLayer
			}
			//Rendering currentLevel

			//currentLevel.m_graphicLayer[2][0].blit({ 0, 0 }, startRectRendering, screenDimension);

			//Render Image
			renderGraphics();
			//Render Image
		}
		//Exploring



		//Battling
		//Battling



		//Dialoging
		//Dialoging
	}

}



void Game::shutdown()
{

}



void Game::runLoop()
{
	while (m_isRunning)
	{
		updateDeltaTime();

		//Clear Render
		SDL_RenderClear(SDL_Handler::get().getRenderer());
		//Clear Render

		processInput();

		update();
		
		generateOutput();

		sleep();
	}
}
//------------------------------------------------------------------------------------
//Game Class
//------------------------------------------------------------------------------------