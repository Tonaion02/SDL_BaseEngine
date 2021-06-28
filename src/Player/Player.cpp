#include "Player/Player.h"





//------------------------------------------------------------------------------------
//Player Class
//------------------------------------------------------------------------------------
Player::Player(const std::string& filePath)
{
	interaction.typeInteraction = TypeInteraction::NoneTypeInteraction;
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

					int wewe = tileMap.m_uniqueTileLayer.m_indexMatrix[lastPos.y + j][lastPos.x + i];

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
		}
	}


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
				CommonTile tile = tileMap.getCommonTile(pos.x + i, pos.y + j, z);

				if (tile.isUnique())
				{
					switch (tile.realType)
					{
					case Chest:
					case Destructble:
					case Openable:
						interactiveAnimation.setPos(posImage);
						interactiveAnimation.start();
						updateActivity(PlayerActivity::PlayerInteracting);
						interaction.typeInteraction = TypeInteraction::WithTile;
						interaction.poses.push_back({ pos.x + i, pos.y + j });
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
						interactiveAnimation.setPos(posImage);
						interactiveAnimation.start();
						updateActivity(PlayerActivity::PlayerInteracting);
						interaction.typeInteraction = TypeInteraction::WithTile;
						interaction.poses.push_back({ pos.x + i, pos.y + j });
						break;

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
	if (currentActivity == PlayerInteracting)
	{
		for (int j = 0; j < nTile.y; j++)
		{
			for (int i = 0; i < nTile.x; i++)
			{
				int addIdImage = ((j)* tileSetHandler.getTileSet(nameTileSet).getColumns()) + i;
				Vector2i p = { posInProspective.x + (i*tileDimension.x), posInProspective.y + (j*tileDimension.y) };
				tileSetHandler.getTileSet(nameTileSet).blitImageTile(interactiveAnimation.getIdImage() + addIdImage, p);
			}
		}
	}
	


	if (currentActivity == PlayerExploring)
	{
		render(posInProspective, tileSetHandler);
	}
}
//------------------------------------------------------------------------------------
//Player Class
//------------------------------------------------------------------------------------