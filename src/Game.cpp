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
//-Creare funzione che permette di andare a modificare gli fps(importante controllare se è vsync e nel caso non farlo aggiornare)
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



void Game::clearRender()
{
	//Clear Render
	SDL_RenderClear(SDL_Handler::get().getRenderer());
	//Clear Render
}



void Game::renderGraphics()
{
	SDL_RenderPresent(SDL_Handler::get().getRenderer());
}





void Game::changeLevel()
{
	for (int j = 0; j < s_player.nTile.y; j++)
	{
		for (int i = 0; i < s_player.nTile.x; i++)
		{
			CommonTile commonTile = currentLevel.m_tileMaps[s_player.z].getCommonTile(s_player.pos.x + i, s_player.pos.y + j, 0);

			if (commonTile.realType == RealType::Transition)
			{
				TransitionTile tile = currentLevel.m_tileMaps[s_player.z].m_uniqueTileLayer.m_transitionTiles[
					currentLevel.m_tileMaps[s_player.z].m_uniqueTileLayer.m_indexMatrix[s_player.pos.y + j][s_player.pos.x + i]];

				s_player.z = tile.nextLevelZ;
				s_player.lastZ = s_player.z;

				s_player.pos = tile.nextLevelPos;
				s_player.lastPos = tile.nextLevelPos;
				s_player.changingLevel = false;
				currentLevel = World::get().getLevel(World::get().getIndexLevel(tile.nameLevel));
				s_player.posImage = { s_player.pos.x * currentLevel.getTileWidth(), s_player.pos.y * currentLevel.getTileHeight() };

				statusHandler.getStatus(statusHandler.searchStatus(GamePhase::Phase::Exploring)).status = GamePhase::StatusGamePhase::On;

				return;
			}
		}
	}
}





void Game::first()
{
	if (m_isFirst)
	{
		m_isFirst = false;

		World::get().loadLevel("Level5.tmx", entityTileSetHandler);
		World::get().loadLevel("Level6.tmx", entityTileSetHandler);
		currentLevel = World::get().getLevel(World::get().getIndexLevel("Level6.tmx"));

		s_player.rotateHitboxWithDirection = false;
		//s_player.pos = Vector2i(50.0f, 50.0f );
		s_player.pos = Vector2i(50.0f, 11.0f);
		s_player.lastPos = s_player.pos;
		s_player.posImage = { s_player.pos.x * currentLevel.getTileWidth(), s_player.pos.y * currentLevel.getTileHeight() };
		s_player.z = 0;
		s_player.lastZ = s_player.z;

		statusHandler.addStatus(GamePhase(GamePhase::Phase::Exploring));
		statusHandler.getStatus(statusHandler.searchStatus(GamePhase(GamePhase::Phase::Exploring))).status = GamePhase::StatusGamePhase::On;

		TileSet tileSet = TileSet("data/tileset/playerTileSet16.tsx", 0, false);
		entityTileSetHandler.addTileSet(tileSet);

		s_player.tileDimension = { currentLevel.getTileWidth(), currentLevel.getTileHeight() };
		
		s_player.animations.push_back(std::vector<std::vector<DinamicAnimation>>(0));
		s_player.animations.push_back(std::vector<std::vector<DinamicAnimation>>(0));

		for (int i = 0; i < s_player.animations.size(); i++)
		{
			for (int j = 0; j < 2; j++)
			{
				s_player.animations[i].push_back(std::vector<DinamicAnimation>(0));
			}
		}

		//s_player.animations[0][0].push_back(DinamicAnimation({ 1, 0, 2 }, "playerTileSet16.tsx", 0.6f, s_player.pos, 0.6f, { 0, -currentLevel.getTileHeight() }));
		//s_player.animations[0][0].push_back(DinamicAnimation({ 4, 3, 5 }, "playerTileSet16.tsx", 0.6f, s_player.pos, 0.6f, { 0, currentLevel.getTileHeight() }));
		//s_player.animations[0][0].push_back(DinamicAnimation({ 10, 9, 11 }, "playerTileSet16.tsx", 0.6f, s_player.pos, 0.6f, { currentLevel.getTileWidth(), 0 }));
		//s_player.animations[0][0].push_back(DinamicAnimation({ 7, 6, 8 }, "playerTileSet16.tsx", 0.6f, s_player.pos, 0.6f, { -currentLevel.getTileWidth(), 0 }));

		s_player.animations[0][0].push_back(DinamicAnimation({ 1, 0, 2 }, "playerTileSet16.tsx", 0.2f, s_player.pos, 0.2f, { 0, -currentLevel.getTileHeight() }));
		s_player.animations[0][0].push_back(DinamicAnimation({ 4, 3, 5 }, "playerTileSet16.tsx", 0.2f, s_player.pos, 0.2f, { 0, currentLevel.getTileHeight() }));
		s_player.animations[0][0].push_back(DinamicAnimation({ 10, 9, 11 }, "playerTileSet16.tsx", 0.2f, s_player.pos, 0.2f, { currentLevel.getTileWidth(), 0 }));
		s_player.animations[0][0].push_back(DinamicAnimation({ 7, 6, 8 }, "playerTileSet16.tsx", 0.2f, s_player.pos, 0.2f, { -currentLevel.getTileWidth(), 0 }));

		s_player.idStaticImage.push_back(0);
		s_player.idStaticImage.push_back(3);
		s_player.idStaticImage.push_back(9);
		s_player.idStaticImage.push_back(6);

		s_player.interactiveAnimation = StaticAnimation({ 0, 0 }, "playerTileSet16.tsx", 0.2f, s_player.pos);

		s_player.delayChangingLevel = Delay(0.5f);

		currentLevel.m_entityLayers[s_player.z].addPlayer(s_player.pos, s_player.nTile);

		s_ticksCount = 0;

		//Init Camera
		Camera::get().init({ currentLevel.getTileWidth(), currentLevel.getTileHeight() }, { currentLevel.getWidth(), currentLevel.getHeight() });
		//Init Camera



		//Init Test Npc
		//Npc testNpc = Npc();
		//testNpc.pos = { 5, 3 };
		//testNpc.posImage = { testNpc.pos.x * currentLevel.getTileWidth(), testNpc.pos.y * currentLevel.getTileHeight() };
		//testNpc.nTile = { 2, 2 };
		//testNpc.animations = entity.animations;
		//testNpc.idStaticImage = entity.idStaticImage;
		//testNpc.nameTileSet = entity.nameTileSet;
		//testNpc.tileDimension = entity.tileDimension;
		//currentLevel.m_entityLayers[entity.z].add(testNpc);



		//testNpc = Npc();
		//testNpc.pos = { 9, 3 };
		//testNpc.posImage = { testNpc.pos.x * currentLevel.getTileWidth(), testNpc.pos.y * currentLevel.getTileHeight() };
		//testNpc.nTile = { 2, 2 };
		//testNpc.animations = entity.animations;
		//testNpc.idStaticImage = entity.idStaticImage;
		//testNpc.nameTileSet = entity.nameTileSet;
		//testNpc.tileDimension = entity.tileDimension;
		//currentLevel.m_entityLayers[entity.z].add(testNpc);



		//testNpc = Npc();
		//testNpc.pos = { 6, 1 };
		//testNpc.posImage = { testNpc.pos.x * currentLevel.getTileWidth(), testNpc.pos.y * currentLevel.getTileHeight() };
		//testNpc.nTile = { 2, 2 };
		//testNpc.animations = entity.animations;
		//testNpc.idStaticImage = entity.idStaticImage;
		//testNpc.nameTileSet = entity.nameTileSet;
		//testNpc.tileDimension = entity.tileDimension;
		//currentLevel.m_entityLayers[entity.z].add(testNpc);



		//testNpc = Npc();
		//testNpc.pos = { 7, 5 };
		//testNpc.posImage = { testNpc.pos.x * currentLevel.getTileWidth(), testNpc.pos.y * currentLevel.getTileHeight() };
		//testNpc.nTile = { 2, 2 };
		//testNpc.animations = entity.animations;
		//testNpc.idStaticImage = entity.idStaticImage;
		//testNpc.nameTileSet = entity.nameTileSet;
		//testNpc.tileDimension = entity.tileDimension;
		//currentLevel.m_entityLayers[entity.z].add(testNpc);
		//Init Test Npc



		//Init Test Enemy
		Enemy testEnemy = Enemy();
		testEnemy.z = s_player.z;
		testEnemy.pos = { 12, 3 };
		testEnemy.posImage = { testEnemy.pos.x * currentLevel.getTileWidth(), testEnemy.pos.y * currentLevel.getTileHeight() };
		testEnemy.nTile = { 2, 2 };
		testEnemy.animations = s_player.animations;
		testEnemy.idStaticImage = s_player.idStaticImage;
		testEnemy.nameTileSet = s_player.nameTileSet;
		testEnemy.tileDimension = s_player.tileDimension;
		testEnemy.viewLenght = 2;
		testEnemy.lastDirection = Direction::Right;
		testEnemy.allertingAnimation = StaticAnimation({ 0 , 1 }, "playerTileSet16.tsx", 0.2f, {0, 0});
		//testEnemy.allertingAnimation.loop();
		testEnemy.delayChangeDirection = Delay(0.2f);
		std::vector<Direction> steps;
		//steps.push_back(Direction::Down);
		//steps.push_back(Direction::Down);
		//steps.push_back(Direction::Left);
		//steps.push_back(Direction::Down);
		//steps.push_back(Direction::Down);
		//steps.push_back(Direction::Down);
		//steps.push_back(Direction::Down);

		steps.push_back(Direction::Left);
		steps.push_back(Direction::Left);
		steps.push_back(Direction::Left);
		steps.push_back(Direction::Left);
		steps.push_back(Direction::Right);
		steps.push_back(Direction::Right);
		steps.push_back(Direction::Right);
		steps.push_back(Direction::Right);

		testEnemy.route = Route(steps);
		testEnemy.withRoute = true;
		testEnemy.stop = true;

		testEnemy.delayNextStep = Delay(0.5f);

		currentLevel.m_entityLayers[s_player.z].add(testEnemy);
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
	InputHandler::get().update();

	if (InputHandler::get().isPressed(SDL_SCANCODE_ESCAPE))
	{
		m_isRunning = false;
	}

	if (InputHandler::get().isQuit())
	{
		m_isRunning = false;
	}

	//SDL_Log(std::to_string(InputHandler::get().getPos().x).c_str());
	//SDL_Log(std::to_string(InputHandler::get().isMousePressed(2)).c_str());
}



void Game::update()
{
	first();

	for (int indexPhase = statusHandler.getSize()-1; indexPhase >= 0; indexPhase--)
	{
		GamePhase actualPhase = statusHandler.getStatus(indexPhase);
		GamePhase::StatusGamePhase statusActualPhase = statusHandler.getStatus(indexPhase).status;

		//Exploring
		if (actualPhase.phase == GamePhase::Phase::Exploring && statusActualPhase != GamePhase::StatusGamePhase::Off)
		{
			//Verify if a Battle is Started
			if (statusHandler.searchStatus(GamePhase::Phase::Battle) == -1)
			{
				//Verify if an Entity see the Player
				int indexEnemy = -1;
				for (auto& cEnemy : currentLevel.m_entityLayers[s_player.z].m_enemies)
				{
					indexEnemy++;
					if (s_player.statusMovement == StatusMovement::Lock)
					{
						if (cEnemy.statusMovement == StatusMovement::Lock && cEnemy.statusFighting == StatusFighting::Alive && cEnemy.currentActivity == ActivityEnemy::Exploring)
						{
							if (cEnemy.detectPlayer(currentLevel.m_tileMaps[s_player.z], currentLevel.m_entityLayers[s_player.z].m_idEntities))
							{
								SDL_Log("heyyyyyyyy");
								cEnemy.currentActivity = ActivityEnemy::Allerting;
								cEnemy.allertingAnimation.setPos({ cEnemy.posImage.x, cEnemy.posImage.y - cEnemy.tileDimension.y });
								cEnemy.allertingAnimation.start();

								currentEnemy = indexEnemy;
								zCurrentEnemy = cEnemy.z;

								GamePhase battlePhase = GamePhase(GamePhase::Phase::Battle);
								battlePhase.status = GamePhase::StatusGamePhase::Off;
								statusHandler.addStatus(battlePhase);
								statusHandler.getStatus(statusHandler.searchStatus(GamePhase::Phase::Exploring)).status = GamePhase::StatusGamePhase::Pause;
							}
						}
					}
				}
				//Verify if an Entity see the Player
			}
			//Verify if a Battle is Started



			//Verify if Exploring Phase is On
			if (statusHandler.searchStatus(GamePhase::Phase::Exploring) != -1
				&& statusHandler.getStatus(statusHandler.searchStatus(GamePhase::Phase::Exploring)).status == GamePhase::StatusGamePhase::On)
			{
				//Update Player Direction
				if (s_player.currentActivity == PlayerActivity::PlayerExploring)
				{
					if (s_player.statusMovement == StatusMovement::Lock)
					{
						if (InputHandler::get().isPressed(SDL_SCANCODE_W))
						{
							s_player.startMove(Direction::Up, currentLevel.m_tileMaps[s_player.z], currentLevel.m_entityLayers[s_player.z].m_idEntities);
						}
						else if (InputHandler::get().isPressed(SDL_SCANCODE_S))
						{
							s_player.startMove(Direction::Down, currentLevel.m_tileMaps[s_player.z], currentLevel.m_entityLayers[s_player.z].m_idEntities);
						}
						else if (InputHandler::get().isPressed(SDL_SCANCODE_D))
						{
							s_player.startMove(Direction::Right, currentLevel.m_tileMaps[s_player.z], currentLevel.m_entityLayers[s_player.z].m_idEntities);
						}
						else if (InputHandler::get().isPressed(SDL_SCANCODE_A))
						{
							s_player.startMove(Direction::Left, currentLevel.m_tileMaps[s_player.z], currentLevel.m_entityLayers[s_player.z].m_idEntities);
						}
						else if (InputHandler::get().isPressed(SDL_SCANCODE_B))
						{
							s_player.tryToInteract(currentLevel.m_tileMaps[s_player.z], currentLevel.m_entityLayers[s_player.z].m_idEntities);
						}
					}
				}
				//Update Player Direction
			}
			//Verify if Exploring Phase is On



			//Execute in case that GamePhase Exploring is in Pause
			if (statusHandler.searchStatus(GamePhase::Phase::Exploring) != -1
				&& statusHandler.getStatus(statusHandler.searchStatus(GamePhase::Phase::Exploring)).status == GamePhase::StatusGamePhase::Pause)
			{
				//Verify when is terminated the animation of player or entity after starting of battle
				if (statusHandler.searchStatus(GamePhase::Phase::Battle) != -1
					&& statusHandler.getStatus(statusHandler.searchStatus(GamePhase::Phase::Battle)).status == GamePhase::StatusGamePhase::Off)
				{
					//Aggiungere controllo se ha terminato l'animazione il player
					if (currentLevel.m_entityLayers[s_player.z].m_enemies[currentEnemy].currentActivity == ActivityEnemy::Fighting)
					{
						statusHandler.getStatus(indexPhase).status = GamePhase::StatusGamePhase::Off;
						statusHandler.getStatus(statusHandler.searchStatus(GamePhase::Phase::Battle)).status = GamePhase::StatusGamePhase::On;
					}
					else
					{
						currentLevel.m_entityLayers[zCurrentEnemy].m_enemies[currentEnemy].updateEnemy(s_deltaTime, 
							currentLevel.m_tileMaps[zCurrentEnemy], 
							currentLevel.m_entityLayers[zCurrentEnemy].m_idEntities);
					}
				}
				//Verify when is terminated the animation of player or entity after starting of battle
			}
			//Execute in case that GamePhase Exploring is in Pause



			//Execute in any case
			//Update Player
			s_player.updatePlayer(s_deltaTime, currentLevel.m_tileMaps[s_player.z], currentLevel.m_entityLayers[s_player.z].m_idEntities);
			if (s_player.z != s_player.lastZ)
			{
				idEntity id = currentLevel.m_entityLayers[s_player.lastZ].m_idEntities[s_player.pos.y][s_player.pos.x];

				//Clear other cells

				for (int j = 0; j < s_player.nTile.y; j++)
				{
					for (int i = 0; i < s_player.nTile.x; i++)
					{
						Vector2i p = { s_player.pos.x + i, s_player.pos.y + j };

						currentLevel.m_entityLayers[s_player.lastZ].m_idEntities[p.y][p.x] = 
							idEntity(TypeEntity::NoneTypeEntity, -1);
					}
				}
				//Clear other cells

				for (int j = 0; j < s_player.nTile.y; j++)
				{
					for (int i = 0; i < s_player.nTile.x; i++)
					{
						Vector2i p = { s_player.pos.x + i, s_player.pos.y + j };

						currentLevel.m_entityLayers[s_player.z].m_idEntities[p.y][p.x] = id;
					}
				}

				s_player.lastZ = s_player.z;
			}
			if (s_player.changingLevel)
			{
				statusHandler.getStatus(statusHandler.searchStatus(GamePhase::Exploring)).status = GamePhase::StatusGamePhase::Pause;
				if (s_player.delayChangingLevel.isEnd())
				{
					Game::changeLevel();
				}

				//else
				//{
				//	s_player.delayChangingLevel.update(s_deltaTime);
				//}
			}
			//Update Player

			

			//Update Camera Position
			Camera::get().updatePos(s_player.posImage);
			//Update Camera Position

			
			
			//Take decision on Enemy Entities
			if (statusHandler.searchStatus(GamePhase::Phase::Exploring) != -1
				&& statusHandler.getStatus(statusHandler.searchStatus(GamePhase::Phase::Exploring)).status == GamePhase::StatusGamePhase::On)
			{
				for (int z = 0; z < currentLevel.m_tileMaps.size(); z++)
				{
					for (auto& cEnemy : currentLevel.m_entityLayers[z].m_enemies)
					{
						cEnemy.takeDecision(s_deltaTime, currentLevel.m_tileMaps[z], currentLevel.m_entityLayers[z].m_idEntities);
					}
				}
			}
			//Take decision on Enemy Entities



			//Update Npc
			for (int z = 0; z < currentLevel.m_tileMaps.size(); z++)
			{
				for (auto& cNpc : currentLevel.m_entityLayers[z].m_npcs)
				{
					cNpc.update(s_deltaTime, currentLevel.m_tileMaps[z], currentLevel.m_entityLayers[z].m_idEntities);
				}
			}
			//Update Npc



			//Update Enemy
			for (int z = 0; z < currentLevel.m_tileMaps.size(); z++)
			{
				for (auto& cEnemy : currentLevel.m_entityLayers[z].m_enemies)
				{
					cEnemy.updateEnemy(s_deltaTime, currentLevel.m_tileMaps[z], currentLevel.m_entityLayers[z].m_idEntities);
				}
			}
			//Update Enemy
		}
		//Exploring



		//Battling
		else if (actualPhase.phase == GamePhase::Phase::Battle)
		{
			if (statusActualPhase == GamePhase::StatusGamePhase::Pause)
			{
				//Attendere che finiscano le animazioni in exploring(oppure no)
				
			}
			else if (statusActualPhase == GamePhase::StatusGamePhase::On)
			{
				//Battle vera e propria
				SDL_Log("BATTLE!!!!!!!!!!");
			}
			else if (statusActualPhase == GamePhase::StatusGamePhase::Off)
			{

			}
		}
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
		GamePhase::StatusGamePhase statusActualPhase = statusHandler.getStatus(indexPhase).status;

		//Exploring
		if (actualPhase.phase == GamePhase::Phase::Exploring && statusActualPhase != GamePhase::StatusGamePhase::Off)
		{
			if (statusActualPhase == GamePhase::StatusGamePhase::Pause)
			{
				if (s_player.changingLevel)
				{
					Game::get().clearColorScreen(Color(0, 0, 0, 255));
					renderGraphics();
					return;
				}
			}
			//Clear Screen
			Game::get().clearColorScreen(Color(0, 255, 255, 255));
			//Clear Screen

			//Rendering currentLevel
			for (int i = 0; i < currentLevel.m_tileMaps.size(); i++)
			{
				//Rendering First TileLayer
				//currentLevel.m_graphicLayer[i][0].blit({ 0, 0 }, Camera::get().getStartRectRendering(), screenDimension);
				currentLevel.getGraphicLayer(i, 0).blit({ 0, 0 }, Camera::get().getStartRectRendering(), screenDimension);
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
								currentLevel.m_tileSetHandler.blitImageTile(currentLevel.m_tileMaps[i].m_uniqueTileLayer.m_chestTiles[index].getCurrentImage(),
									currentLevel.m_tileMaps[i].m_uniqueTileLayer.m_chestTiles[index].nameTileSet,
									{ rendX, rendY });
								break;
							case Openable:
								break;
							case Stairs:
								currentLevel.m_tileSetHandler.blitImageTile(currentLevel.m_tileMaps[i].m_uniqueTileLayer.m_stairsTiles[index].idImage,
									currentLevel.m_tileMaps[i].m_uniqueTileLayer.m_stairsTiles[index].nameTileSet,
									{ rendX, rendY });
								break;

							case Transition:
								currentLevel.m_tileSetHandler.blitImageTile(currentLevel.m_tileMaps[i].m_uniqueTileLayer.m_transitionTiles[index].idImage,
									currentLevel.m_tileMaps[i].m_uniqueTileLayer.m_transitionTiles[index].nameTileSet,
									{ rendX, rendY });
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
				if (s_player.z == i)
				{
					s_player.render(Camera::get().getPlayerPos(), entityTileSetHandler);
				}
				//Render Player

				//Render Npc
				for (auto cNpc : currentLevel.m_entityLayers[i].m_npcs)
				{
					cNpc.renderNpc(Camera::get().getPosInProspective(cNpc.posImage), entityTileSetHandler);
				}
				//Render Npc

				//Render Npc
				for (auto cEnemy : currentLevel.m_entityLayers[i].m_enemies)
				{
					//cEnemy.render(Camera::get().getPosInProspective(cEnemy.posImage), entityTileSetHandler);
					cEnemy.renderEnemy(Camera::get().getPosInProspective(cEnemy.posImage), entityTileSetHandler);
				}
				//Render Npc

				//Rendering Other TileLayer
				for (int j = 1; j < currentLevel.m_graphicLayer[i].size(); j++)
				{
					//currentLevel.m_graphicLayer[i][j].blit({ 0, 0 }, Camera::get().getStartRectRendering(), screenDimension);
					currentLevel.getGraphicLayer(i, j).blit({ 0, 0 }, Camera::get().getStartRectRendering(), screenDimension);
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
		else if (actualPhase.phase == GamePhase::Phase::Battle)
		{
			if (statusActualPhase == GamePhase::StatusGamePhase::On)
			{
				//Clear Screen
				Game::get().clearColorScreen(Color(0, 0, 0, 0));
				//Clear Screen
				
				//Render Image
				renderGraphics();
				//Render Image
			}
			else if (statusActualPhase == GamePhase::StatusGamePhase::Pause)
			{

			}
		}
		//Battling



		//Dialoging
		else if (actualPhase.phase == GamePhase::Phase::Dialoging)
		{
			if (statusActualPhase == GamePhase::StatusGamePhase::On)
			{
				//Write dialog
			}
		}
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
		
		clearRender();

		processInput();

		update();
		
		generateOutput();

		sleep();
	}
}
//------------------------------------------------------------------------------------
//Game Class
//------------------------------------------------------------------------------------