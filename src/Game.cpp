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

		entity.rotateHitboxWithDirection = false;
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

		entity.animations[0][0].push_back(DinamicAnimation({ 0, 0 }, "playerTileSet16.tsx", 0.2f, entity.pos, 0.2f, { 0, -currentLevel.getTileHeight() }));
		entity.animations[0][0].push_back(DinamicAnimation({ 0, 0 }, "playerTileSet16.tsx", 0.2f, entity.pos, 0.2f, { 0, currentLevel.getTileHeight() }));
		entity.animations[0][0].push_back(DinamicAnimation({ 0, 0 }, "playerTileSet16.tsx", 0.2f, entity.pos, 0.2f, { currentLevel.getTileWidth(), 0 }));
		entity.animations[0][0].push_back(DinamicAnimation({ 0, 0 }, "playerTileSet16.tsx", 0.2f, entity.pos, 0.2f, { -currentLevel.getTileWidth(), 0 }));

		entity.idStaticImage.push_back(0);
		entity.idStaticImage.push_back(0);
		entity.idStaticImage.push_back(0);
		entity.idStaticImage.push_back(0);

		currentLevel.m_entityLayers[entity.z].addPlayer(entity.pos, entity.nTile);

		s_ticksCount = 0;

		//Init Camera
		Camera::get().init({ currentLevel.getTileWidth(), currentLevel.getTileHeight() }, { currentLevel.getWidth(), currentLevel.getHeight() });
		//Init Camera



		//Init Test Npc
		Npc testNpc = Npc();
		testNpc.pos = { 3, 3 };
		testNpc.posImage = { testNpc.pos.x * currentLevel.getTileWidth(), testNpc.pos.y * currentLevel.getTileHeight() };
		testNpc.nTile = { 2, 2 };
		testNpc.animations = entity.animations;
		testNpc.idStaticImage = entity.idStaticImage;
		testNpc.nameTileSet = entity.nameTileSet;
		testNpc.tileDimension = entity.tileDimension;
		currentLevel.m_entityLayers[entity.z].add(testNpc);
		//Init Test Npc



		//Init Test Enemy
		Enemy testEnemy = Enemy();
		testEnemy.pos = { 6, 3 };
		testEnemy.posImage = { testEnemy.pos.x * currentLevel.getTileWidth(), testEnemy.pos.y * currentLevel.getTileHeight() };
		testEnemy.nTile = { 2, 2 };
		testEnemy.animations = entity.animations;
		testEnemy.idStaticImage = entity.idStaticImage;
		testEnemy.nameTileSet = entity.nameTileSet;
		testEnemy.tileDimension = entity.tileDimension;
		testEnemy.viewLenght = 2;
		testEnemy.lastDirection = Direction::Right;
		currentLevel.m_entityLayers[entity.z].add(testEnemy);
		//Init Test Enemy
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
			//Update Player
			if (entity.statusMovement == StatusMovement::Lock)
			{
				if (InputHandler::get().isPressed(SDL_SCANCODE_W))
				{
					entity.startMove(Direction::Up, currentLevel.m_tileMaps[entity.z], currentLevel.m_entityLayers[entity.z].m_idEntities);
				}
				else if (InputHandler::get().isPressed(SDL_SCANCODE_S))
				{
					entity.startMove(Direction::Down, currentLevel.m_tileMaps[entity.z], currentLevel.m_entityLayers[entity.z].m_idEntities);
				}
				else if (InputHandler::get().isPressed(SDL_SCANCODE_D))
				{
					entity.startMove(Direction::Right, currentLevel.m_tileMaps[entity.z], currentLevel.m_entityLayers[entity.z].m_idEntities);
				}
				else if (InputHandler::get().isPressed(SDL_SCANCODE_A))
				{
					entity.startMove(Direction::Left, currentLevel.m_tileMaps[entity.z], currentLevel.m_entityLayers[entity.z].m_idEntities);
				}
			}

			entity.update(s_deltaTime, currentLevel.m_tileMaps[entity.z], currentLevel.m_entityLayers[entity.z].m_idEntities);
			Camera::get().updatePos(entity.posImage);
			//Update Player

			//Update Npc
			for (int z = 0; z < currentLevel.m_tileMaps.size(); z++)
			{
				for (auto cNpc : currentLevel.m_entityLayers[z].m_npcs)
				{
					cNpc.update(s_deltaTime, currentLevel.m_tileMaps[z], currentLevel.m_entityLayers[z].m_idEntities);
				}
			}
			//Update Npc

			//Update Enemy
			for (int z = 0; z < currentLevel.m_tileMaps.size(); z++)
			{
				for (auto cEnemy : currentLevel.m_entityLayers[z].m_enemies)
				{
					cEnemy.update(s_deltaTime, currentLevel.m_tileMaps[z], currentLevel.m_entityLayers[z].m_idEntities);
					if (cEnemy.detectPlayer(currentLevel.m_entityLayers[z].m_idEntities))
					{
						SDL_Log("heyyyyyyyyy");
					}
				}
			}
			//Update Enemy
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
					entity.render(Camera::get().getPlayerPos(), entityTileSetHandler);
				}
				//Render Player

				//Render Npc
				for (auto cNpc : currentLevel.m_entityLayers[i].m_npcs)
				{
					cNpc.render(Camera::get().getPosInProspective(cNpc.posImage), entityTileSetHandler);
				}
				//Render Npc

				//Render Npc
				for (auto cEnemy : currentLevel.m_entityLayers[i].m_enemies)
				{
					cEnemy.render(Camera::get().getPosInProspective(cEnemy.posImage), entityTileSetHandler);
				}
				//Render Npc

				//Rendering Other TileLayer
				for (int j = 1; j < currentLevel.m_graphicLayer[i].size(); j++)
				{
					currentLevel.m_graphicLayer[i][j].blit({ 0, 0 }, Camera::get().getStartRectRendering(), screenDimension);
				}
				//Rendering Other TileLayer
			}
			//Rendering currentLevel

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