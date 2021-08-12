#include "Player/Player.h"





//------------------------------------------------------------------------------------
//Player Class
//------------------------------------------------------------------------------------
Player::Player(const std::string& saveSlot, TileSetHandler& entityTileSet)
{
	interaction.typeInteraction = TypeInteraction::NoneTypeInteraction;
	currentActivity = PlayerActivity::PlayerExploring;

	XMLobject xmlObject = XMLobject("data/player.tx");

	idStaticImage = std::vector<uint16_t>(0);

	animations.push_back(std::vector<std::vector<DinamicAnimation>>(0));
	animations.push_back(std::vector<std::vector<DinamicAnimation>>(0));

	for (int i = 0; i < animations.size(); i++)
	{
		for (int j = 0; j < 2; j++)
		{
			animations[i].push_back(std::vector<DinamicAnimation>(0));
		}
	}

	tileDimension = entityTileSet.getTileDimension();

	interactiveAnimation = StaticAnimation();

	for (int i = 0; i < xmlObject.xmlVariabs.size(); i++)
	{
		XMLvariab var = xmlObject.xmlVariabs[i];

		if (var.name == "tileset")
		{
			nameTileSet = var.getValue("tileset");
		}
		else if (var.name == "nTile")
		{
			std::vector<std::string> splitter = split(var.getValue("value"), ",");
			nTile.x = std::stoi(splitter[0]);
			nTile.y = std::stoi(splitter[1]);
		}
		else if (var.name == "nTileGraphics")
		{
			std::vector<std::string> splitter = split(var.getValue("value"), ",");
			nTileGraphics.x = std::stoi(splitter[0]);
			nTileGraphics.y = std::stoi(splitter[1]);
		}
		else if (var.name == "renderingAdjPos")
		{
			std::vector<std::string> splitter = split(var.getValue("value"), ",");
			renderingAdjPos.x = std::stoi(splitter[0]);
			renderingAdjPos.y = std::stoi(splitter[1]);
		}
		else if (var.name == "direction")
		{
			Direction direction = (Direction)std::stoi(var.getValue("value"));

			if (var.getValue("name") == "lastDirection")
			{
				lastDirection = direction;
			}
		}
		else if(var.name == "condition")	
		{
			bool sem = fromStringToBool(var.getValue("value"));

			if (var.getValue("name") == "rotateHibtoxWithDirection")
			{
				rotateHitboxWithDirection = sem;
			}
		}
		else if (var.name == "idImage")
		{
			std::vector<std::string> splitter = split(var.getValue("value"), ",");
			for (auto info : splitter)
			{
				idStaticImage.push_back(std::stoi(info));
			}
		}
		else if (var.name == "DinamicAnimation")
		{
			std::vector<std::string> splitter = split(var.getValue("images"), ",");
			std::vector<uint16_t> idImages;
			for (auto info : splitter)
			{
				idImages.push_back(std::stoi(info));
			}

			splitter = split(var.getValue("space"), ",");

			DinamicAnimation animation = DinamicAnimation(idImages, 
				var.getValue("tileset"), std::stof(var.getValue("delay")), 
				pos, 
				std::stof(var.getValue("delayMovement")), 
				{std::stoi(splitter[0])*tileDimension.x, std::stoi(splitter[1])*tileDimension.y});

			TypeTerrain surface = (TypeTerrain)std::stoi(var.getValue("surface"));
			Velocity velocity = (Velocity)std::stoi(var.getValue("velocity"));
			
			animations[surface][velocity].push_back(animation);
		}
		else if (var.name == "StaticAnimation")
		{
			std::vector<std::string> splitter = split(var.getValue("images"), ",");
			std::vector<uint16_t> idImages;
			for (auto info : splitter)
			{
				idImages.push_back(std::stoi(info));
			}

			StaticAnimation staticAnimation = StaticAnimation(idImages, var.getValue("tileset"), std::stof(var.getValue("delay")), pos);

			if (var.getValue("name") == "interactionAnimation")
			{
				interactiveAnimation = staticAnimation;
			}

		}
	}

}



void Player::updateActivity(PlayerActivity activity)
{
	currentActivity = activity;
}



void Player::deReact(TileMap& tileMap)
{
	for (int j = 0; j < nTile.y; j++)
	{
		for (int i = 0; i < nTile.x; i++)
		{
			CommonTile commonTile = tileMap.getCommonTile(lastPos.x + i, lastPos.y + j, 0);

			//Fare calcolo dei tile che devono reagire

			if (commonTile.isUnique())
			{
				switch (commonTile.realType)
				{
				case Stairs:
				{
					Direction lastDirectionMovement;

					Vector2i p;
					p.x = pos.x - lastPos.x;
					p.y = pos.y - lastPos.y;

					if (p.y > 0)
					{
						lastDirectionMovement = Direction::Down;
					}
					else if (p.y < 0)
					{
						lastDirectionMovement = Direction::Up;
					}

					else if (p.x > 0)
					{
						lastDirectionMovement = Direction::Right;
					}

					else if (p.x < 0)
					{
						lastDirectionMovement = Direction::Left;
					}

					//int wewe = tileMap.m_uniqueTileLayer.m_indexMatrix[lastPos.y + j][lastPos.x + i];

					if ((Direction)tileMap.m_uniqueTileLayer.m_stairsTiles[tileMap.m_uniqueTileLayer.m_indexMatrix[lastPos.y + j][lastPos.x + i]].direction
						== lastDirectionMovement)
					{
						lastZ = z;
						z = tileMap.m_uniqueTileLayer.m_stairsTiles[tileMap.m_uniqueTileLayer.m_indexMatrix[lastPos.y + j][lastPos.x + i]].z + 1;
						return;
					}
					else if ((Direction)tileMap.m_uniqueTileLayer.m_stairsTiles[tileMap.m_uniqueTileLayer.m_indexMatrix[lastPos.y + j][lastPos.x + i]].direction
						== reverseDirection(lastDirectionMovement))
					{
						lastZ = z;
						z = tileMap.m_uniqueTileLayer.m_stairsTiles[tileMap.m_uniqueTileLayer.m_indexMatrix[lastPos.y + j][lastPos.x + i]].z;
						return;
					}

				}

				}
			}
		}
	}
}



void Player::react(TileMap& tileMap)
{
	for (int j = 0; j < nTile.y; j++)
	{
		for (int i = 0; i < nTile.x; i++)
		{
			CommonTile commonTile = tileMap.getCommonTile(pos.x + i, pos.y + j, 0);

			//Fare calcolo dei tile che devono reagire

			if (commonTile.isUnique())
			{
				switch (commonTile.realType)
				{
				case Stairs:
					z = tileMap.m_uniqueTileLayer.m_stairsTiles[tileMap.m_uniqueTileLayer.m_indexMatrix[pos.y + j][pos.x + i]].z;
					return;

				case Transition:
					changingLevel = true;
					delayChangingLevel.start();
					return;

				default:
					break;
				}
			}
			else
			{
				switch (commonTile.realType)
				{
					case Sea:
						return;
				}
			}
		}
	}
}



void Player::startInteraction(const Vector2i& p)
{
	interactiveAnimation.setPos(posImage);
	interactiveAnimation.start();
	updateActivity(PlayerActivity::PlayerInteracting);
	interaction.typeInteraction = TypeInteraction::WithTile;
	interaction.poses.push_back({ p.x, p.y });
}



void Player::tryToInteract(const TileMap& tileMap, const std::vector<std::vector<idEntity>>& idEntities)
{
	if (currentActivity == PlayerActivity::PlayerExploring)
	{
		Vector2i spaceViewStart, spaceViewEnd;

		switch (lastDirection)
		{
		case Up:
			spaceViewStart.x = 0;
			spaceViewEnd.x = nTile.x;
			spaceViewStart.y = -1;
			spaceViewEnd.y = 0;
			break;
		case Down:
			spaceViewStart.x = 0;
			spaceViewEnd.x = nTile.x;
			spaceViewStart.y = nTile.y;
			spaceViewEnd.y = nTile.y + 1;
			break;
		case Right:
			spaceViewStart.x = nTile.x;
			spaceViewEnd.x = nTile.x + 1;
			spaceViewStart.y = 0;
			spaceViewEnd.y = nTile.y;
			break;
		case Left:
			spaceViewStart.x = -1;
			spaceViewEnd.x = 0;
			spaceViewStart.y = 0;
			spaceViewEnd.y = nTile.y;
			break;
		}

		for (int j = spaceViewStart.y; j < spaceViewEnd.y; j++)
		{
			for (int i = spaceViewStart.x; i < spaceViewEnd.x; i++)
			{
				CommonTile tile = tileMap.getCommonTile(pos.x + i, pos.y + j, 0);
				Vector2i p = { pos.x + i, pos.y + j };

				if (tile.isUnique())
				{
					switch (tile.realType)
					{
					case Chest:
						if (!tileMap.m_uniqueTileLayer.m_chestTiles[tileMap.m_uniqueTileLayer.m_indexMatrix[p.y][p.x]].isOpened)
						{
							startInteraction(p);
						}
						break;
					case Destructble:
						if (!tileMap.m_uniqueTileLayer.m_destructbleTiles[tileMap.m_uniqueTileLayer.m_indexMatrix[p.y][p.x]].isDestroyed)
						{
							startInteraction(p);
						}
						break;
					case Openable:
						if (!tileMap.m_uniqueTileLayer.m_openableTiles[tileMap.m_uniqueTileLayer.m_indexMatrix[p.y][p.x]].isOpened)
						{
							startInteraction(p);
						}
						break;

					default:
						break;
					}
				}
				else
				{
					switch (tile.realType)
					{
					case Sea:
					{
						if (typeTerrain != TypeTerrain::Liquid)
						{
							Vector2i startPosToControll, endPosToControll;

							switch (lastDirection)
							{
							case Up:
								startPosToControll.x = 0;
								startPosToControll.y = -nTile.y;
								endPosToControll.x = nTile.x;
								endPosToControll.y = -1;
								break;
							case Down:
								startPosToControll.x = 0;
								startPosToControll.y = 1;
								endPosToControll.x = nTile.x;
								endPosToControll.y = nTile.y;
								break;
							case Right:
								startPosToControll.x = 1;
								startPosToControll.y = 0;
								endPosToControll.x = nTile.x;
								endPosToControll.y = nTile.y;
								break;
							case Left:
								startPosToControll.x = -nTile.x;
								startPosToControll.y = 0;
								endPosToControll.x = -1;
								endPosToControll.y = nTile.y;
								break;
							}

							for (int y = startPosToControll.y; y < endPosToControll.y; y++)
							{
								for (int x = startPosToControll.x; x < endPosToControll.x; x++)
								{
									Vector2i t = { pos.x + x, pos.y + y };

									if (!isInLimit(t, tileMap))
									{
										return;
									}

									if (!isWithouthEntity(t, idEntities))
									{
										return;
									}

									if (!tileMap.getCommonTile(t.x, t.y, 0).isSea())
									{
										return;
									}
								}
							}

							startInteraction(p);
							break;
						}
					}

					case Ground:
					{
						if (typeTerrain != TypeTerrain::Solid)
						{
							Vector2i startPosToControll, endPosToControll;

							switch (lastDirection)
							{
							case Up:
								startPosToControll.x = 0;
								startPosToControll.y = -nTile.y;
								endPosToControll.x = nTile.x;
								endPosToControll.y = -1;
								break;
							case Down:
								startPosToControll.x = 0;
								startPosToControll.y = 1;
								endPosToControll.x = nTile.x;
								endPosToControll.y = nTile.y;
								break;
							case Right:
								startPosToControll.x = 1;
								startPosToControll.y = 0;
								endPosToControll.x = nTile.x;
								endPosToControll.y = nTile.y;
								break;
							case Left:
								startPosToControll.x = -nTile.x;
								startPosToControll.y = 0;
								endPosToControll.x = -1;
								endPosToControll.y = nTile.y;
								break;
							}

							for (int y = startPosToControll.y; y < endPosToControll.y; y++)
							{
								for (int x = startPosToControll.x; x < endPosToControll.x; x++)
								{
									Vector2i t = { pos.x + x, pos.y + y };

									if (!isInLimit(t, tileMap))
									{
										return;
									}

									if (!isWithouthEntity(t, idEntities))
									{
										return;
									}

									if (!tileMap.getCommonTile(t.x, t.y, 0).isWalkable())
									{
										return;
									}
								}
							}

							startInteraction(p);
							break;
						}
					}


					default:
						break;
					}
				}
			}
		}
	}

}



void Player::resetInteraction()
{
	//Reset Interaction and Player Status
	interaction.typeInteraction = TypeInteraction::NoneTypeInteraction;
	interaction.poses.clear();
	updateActivity(PlayerActivity::PlayerExploring);
	//Reset Interaction and Player Status
}



void Player::updatePlayer(float deltaTime, TileMap& tileMap, std::vector<std::vector<idEntity>>& idEntities)
{

	if (currentActivity == PlayerActivity::PlayerExploring)
	{
		//update the rest of Player
		update(deltaTime, tileMap, idEntities);
		//update the rest of Player
	}
	else if (currentActivity == PlayerActivity::PlayerInteracting)
	{
		//update interaction animation
		if (!interactiveAnimation.isEnd())
		{
			interactiveAnimation.animate(deltaTime);
		}
		else
		{
			//Quando finisce l'animazione dell'interazione
			for (int i = 0; i < interaction.poses.size(); i++)
			{
				if (interaction.typeInteraction == TypeInteraction::WithTile)
				{
					CommonTile& tile = tileMap.getCommonTile(interaction.poses[i].x, interaction.poses[i].y, 0);

					if (tile.isUnique())
					{
						switch (tile.realType)
						{
						case Chest:
							if (!tileMap.m_uniqueTileLayer.m_chestTiles[tileMap.m_uniqueTileLayer.m_indexMatrix[interaction.poses[i].y][interaction.poses[i].x]].isOpened)
							{
								tileMap.m_uniqueTileLayer.m_chestTiles[tileMap.m_uniqueTileLayer.m_indexMatrix[interaction.poses[i].y][interaction.poses[i].x]].isOpened =
									!tileMap.m_uniqueTileLayer.m_chestTiles[tileMap.m_uniqueTileLayer.m_indexMatrix[interaction.poses[i].y][interaction.poses[i].x]].isOpened;
								resetInteraction();
								return;
							}
							break;
						case Destructble:
							if (!tileMap.m_uniqueTileLayer.m_destructbleTiles[tileMap.m_uniqueTileLayer.m_indexMatrix[interaction.poses[i].y][interaction.poses[i].x]].isDestroyed)
							{
								tileMap.m_uniqueTileLayer.m_destructbleTiles[tileMap.m_uniqueTileLayer.m_indexMatrix[interaction.poses[i].y][interaction.poses[i].x]].isDestroyed =
									!tileMap.m_uniqueTileLayer.m_destructbleTiles[tileMap.m_uniqueTileLayer.m_indexMatrix[interaction.poses[i].y][interaction.poses[i].x]].isDestroyed;
								resetInteraction();
								return;
							}
							break;
						case Openable:
							break;
						default:
							break;
						}
					}
					else
					{
						switch (tile.realType)
						{
						case Sea:
							typeTerrain = TypeTerrain::Liquid;

							switch (lastDirection)
							{
							case Up:
								pos.y += -nTile.y;
								break;
							case Down:
								pos.y += nTile.y;
								break;
							case Right:
								pos.x += nTile.x;
								break;
							case Left:
								pos.x += -nTile.x;
								break;
							}
							posImage = { pos.x * tileDimension.x, pos.y * tileDimension.y };
							resetInteraction();
							break;

						case Ground:
							typeTerrain = TypeTerrain::Solid;

							switch (lastDirection)
							{
							case Up:
								pos.y += -nTile.y;
								break;
							case Down:
								pos.y += nTile.y;
								break;
							case Right:
								pos.x += nTile.x;
								break;
							case Left:
								pos.x += -nTile.x;
								break;
							}
							posImage = { pos.x * tileDimension.x, pos.y * tileDimension.y };
							resetInteraction();
							break;

						default:
							break;
						}
					}
				}
				else if (interaction.typeInteraction == TypeInteraction::WithNpc)
				{

				}
			}

			resetInteraction();
			return;
		}
		//update interaction animation
	}
	
	

	if (changingLevel)
	{
		delayChangingLevel.update(deltaTime);
	}
}



void Player::renderPlayer(const Vector2i& posInProspective, const TileSetHandler& tileSetHandler) const
{
	//if (currentActivity == PlayerInteracting)
	//{
	//	for (int j = 0; j < nTile.y; j++)
	//	{
	//		for (int i = 0; i < nTile.x; i++)
	//		{
	//			int addIdImage = ((j)* tileSetHandler.getTileSet(nameTileSet).getColumns()) + i;
	//			Vector2i p = { posInProspective.x + (i*tileDimension.x), posInProspective.y + (j*tileDimension.y) };
	//			tileSetHandler.getTileSet(nameTileSet).blitImageTile(interactiveAnimation.getIdImage() + addIdImage, p);
	//		}
	//	}
	//}
	if (currentActivity == PlayerInteracting)
	{
		for (int j = 0; j < nTileGraphics.y; j++)
		{
			for (int i = 0; i < nTileGraphics.x; i++)
			{
				int addIdImage = ((j)* tileSetHandler.getTileSet(nameTileSet).getColumns()) + i;
				Vector2i p = { posInProspective.x + (i*tileDimension.x) + (renderingAdjPos.x*tileDimension.x),
					posInProspective.y + (j*tileDimension.y) + (renderingAdjPos.y*tileDimension.y) };
				tileSetHandler.getTileSet(nameTileSet).blitImageTile(interactiveAnimation.getIdImage() + addIdImage, p);
			}
		}
	}


	if (currentActivity == PlayerExploring)
	{
		//render(posInProspective, tileSetHandler);

		for (int j = 0; j < nTileGraphics.y; j++)
		{
			for (int i = 0; i < nTileGraphics.x; i++)
			{
				int addIdImage = ((j)* tileSetHandler.getTileSet(nameTileSet).getColumns()) + i;
				
				Vector2i p = { posInProspective.x + (i*tileDimension.x) + (renderingAdjPos.x*tileDimension.x), 
					posInProspective.y + (j*tileDimension.y) + (renderingAdjPos.y*tileDimension.y) };
				
				tileSetHandler.getTileSet(nameTileSet).blitImageTile(getIdImage() + addIdImage, p);
			}
		}
	}
}
//------------------------------------------------------------------------------------
//Player Class
//------------------------------------------------------------------------------------