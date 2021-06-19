#include "EntityTileMap.h"





bool Entity::isOccupied(const Vector2i& p, idEntity id, const std::vector<std::vector<idEntity>>& idEntities)
{
	return (idEntities[p.y][p.x].index != id.index || idEntities[p.y][p.x].typeEntity != id.typeEntity) && idEntities[p.y][p.x].typeEntity != TypeEntity::NoneTypeEntity;
}



int Entity::getIndexEntity(const Vector2i& p, const std::vector<std::vector<idEntity>>& idEntities)
{
	return idEntities[p.y][p.x].index;
}



idEntity Entity::getIdEntity(const Vector2i& p, const std::vector<std::vector<idEntity>>& idEntities)
{
	return idEntities[p.y][p.x];
}





//------------------------------------------------------------------------------------
//Entity Class
//------------------------------------------------------------------------------------
void Entity::move(Direction direction, std::vector<std::vector<idEntity>>& idEntities)
{
	//Clear other cells
	idEntity id = idEntities[pos.y][pos.x];

	for (int j = 0; j < nTile.y; j++)
	{
		for (int i = 0; i < nTile.x; i++)
		{
			Vector2i p = { pos.x + i, pos.y + j };

			idEntities[p.y][p.x] = idEntity(TypeEntity::NoneTypeEntity, -1);
		}
	}
	//Clear other cells

	switch (currentDirection)
	{
	case NoneDirection:
		break;
	case Up:
		pos.y--;
		break;
	case Down:
		pos.y++;
		break;
	case Right:
		pos.x++;
		break;
	case Left:
		pos.x--;
		break;
	}

	for (int j = 0; j < nTile.y; j++)
	{
		for (int i = 0; i < nTile.x; i++)
		{
			Vector2i p = { pos.x + i, pos.y + j };

			idEntities[p.y][p.x] = id;
		}
	}
}



void Entity::startMove(Direction direction, TileMap& tileMap, std::vector<std::vector<idEntity>>& idEntities)
{
	if (direction != Direction::NoneDirection)
	{
		if (direction != lastDirection)
		{
			delayChangeDirection.start();

			bool canRotate = true;

			if (lastDirection != direction && rotateHitboxWithDirection)
			{
				if ( ((lastDirection == Direction::Down || lastDirection == Direction::Up) && (direction == Direction::Left || direction == Direction::Right)) || ((lastDirection == Direction::Left || lastDirection == Direction::Right) && (direction == Direction::Down || direction == Direction::Up)) )
				{
					idEntity id = getIdEntity(pos, idEntities);
					canRotate = controllPosition(pos, tileMap, idEntities);

					if (canRotate)
					{
						for (int j = 0; j < nTile.y; j++)
						{
							for (int i = 0; i < nTile.x; i++)
							{
								Vector2i p = { pos.x + i, pos.y + j };
								idEntities[p.y][p.x] = idEntity(TypeEntity::NoneTypeEntity, -1);
							}
						}

						nTile = { nTile.y, nTile.x };

						for (int j = 0; j < nTile.y; j++)
						{
							for (int i = 0; i < nTile.x; i++)
							{
								Vector2i p = { pos.x + i, pos.y + j };
								idEntities[p.y][p.x] = id;
							}
						}
					}
				}
			}

			if (canRotate)
			{
				lastDirection = direction;
			}
		}

		else if (delayChangeDirection.isEnd())
		{
			updateDirection(direction);
		}
	}
}



void Entity::updateVelocity(Velocity velocity)
{
	if (velocity != Velocity::NoneVelocity)
	{
		this->velocity = velocity;
	}
}



void Entity::updateSurface(TypeTerrain typeTerrain)
{
	//Per ora solamente questo
	//Aggiungere controllo riguardante il tile davanti
	this->typeTerrain = typeTerrain;
}



void Entity::updateDirection(Direction direction)
{
	if (currentDirection != Direction::NoneDirection)
	{
		lastDirection = currentDirection;
	}
	currentDirection = direction;
}



bool Entity::controllPosition(const Vector2i& t, TileMap& tileMap, const std::vector<std::vector<idEntity>>& idEntities)
{
	//Controllo vero e proprio
	//Controllo sulle dimensioni della TileMap
	if (t.x < 0 || t.x + (nTile.x - 1) >= tileMap.getMaxWidth())
	{
		return false;
	}
	if (t.y < 0 || t.y + (nTile.y - 1) >= tileMap.getMaxHeight())
	{
		return false;
	}
	//Controllo sulle dimensioni della TileMap



	//Controllo del tile sul quale dovrà risiedere il player
	for (int j = 0; j < nTile.y; j++)
	{
		for (int i = 0; i < nTile.x; i++)
		{
			Vector2i p = { t.x + i, t.y + j };
			CommonTile tile = tileMap.getCommonTile(p.x, p.y, 0);

			if (tile.isUnique())
			{
				switch (tile.realType)
				{
				case Destructble:
					if (!tileMap.m_uniqueTileLayer.m_destructbleTiles[tileMap.m_uniqueTileLayer.m_indexMatrix[p.y][p.x]].isDestroyed)
					{
						return false;
					}
					break;
				}
			}
			else
			{
				if (typeTerrain == TypeTerrain::Solid && !tile.isWalkable())
				{
					return false;
				}
				if (typeTerrain == TypeTerrain::Liquid && !tile.isSea())
				{
					return false;
				}
			}
		}
	}
	//Controllo del tile sul quale dovrà risiedere il player



	//Controll if tile is occupied from another entity
	//DA TESTARE
	for (int j = 0; j < nTile.y; j++)
	{
		for (int i = 0; i < nTile.x; i++)
		{
			if (isOccupied({ t.x + i, t.y + j }, getIdEntity({ pos.x + i, pos.y + j }, idEntities), idEntities))
			{
				return false;
			}
		}
	}
	//Controll if tile is occupied from another entity

	return true;
}



bool Entity::controllMove(Direction direction, TileMap& tileMap,const std::vector<std::vector<idEntity>>& idEntities)
{
	Vector2i t = pos;

	switch (direction)
	{
	case NoneDirection:
		//Forse assert, ma non credo
		break;
	case Up:
		t.y--;
		break;
	case Down:
		t.y++;
		break;
	case Right:
		t.x++;
		break;
	case Left:
		t.x--;
		break;
	}

	return controllPosition(t, tileMap, idEntities);
}



void Entity::update(float deltaTime, TileMap& tileMap, std::vector<std::vector<idEntity>>& idEntities)
{
	//Update delay
	delayChangeDirection.update(deltaTime);
	//Update delay


	if (statusMovement == StatusMovement::Lock)
	{
		//currentDirection = NoneDirection;
		if (currentDirection != Direction::NoneDirection)
		{
			//Due casi differenti se effettivamente la currentDirection è uguale a 
			if (controllMove(currentDirection, tileMap, idEntities))
			{
				move(currentDirection, idEntities);

				statusMovement = StatusMovement::InMovement;
				animations[typeTerrain][velocity][currentDirection].setPos(posImage);
				animations[typeTerrain][velocity][currentDirection].start();
			}
			else
			{
				updateDirection(Direction::NoneDirection);
			}
		}
	}

	else if (statusMovement == StatusMovement::InMovement)
	{
		if (!animations[typeTerrain][velocity][currentDirection].isEnd())
		{
			animations[typeTerrain][velocity][currentDirection].animate(deltaTime);
			posImage = animations[typeTerrain][velocity][currentDirection].getPos();
		}

		if (animations[typeTerrain][velocity][currentDirection].isEnd())
		{
			statusMovement = StatusMovement::Lock;
			updateDirection(Direction::NoneDirection);

			posImage = { pos.x * tileDimension.x,pos.y * tileDimension.y };
		}
	}

}



uint16_t Entity::getIdImage()
{
	if (currentDirection == Direction::NoneDirection)
	{
		return idStaticImage[lastDirection];
	}
	else if (currentDirection != Direction::NoneDirection)
	{
		return animations[typeTerrain][velocity][currentDirection].getIdImage();
	}
}



void Entity::render(const Vector2i& posInProspective, const TileSetHandler& tileSetHandler)
{
	for (int j = 0; j < nTile.y; j++)
	{
		for (int i = 0; i < nTile.x; i++)
		{
			int addIdImage = ((j) * tileSetHandler.getTileSet(nameTileSet).getColumns()) + i;
			Vector2i p = { posInProspective.x + (i*tileDimension.x), posInProspective.y + (j*tileDimension.y) };
			tileSetHandler.getTileSet(nameTileSet).blitImageTile(getIdImage() + addIdImage, p);
		}
	}
}
//------------------------------------------------------------------------------------
//Entity Class
//------------------------------------------------------------------------------------





//------------------------------------------------------------------------------------
//Npc Class                                                                           
//------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------
//Npc Class                                                                           
//------------------------------------------------------------------------------------





//------------------------------------------------------------------------------------
//Enemy Class                                                                           
//------------------------------------------------------------------------------------
bool Enemy::detectPlayer(const std::vector<std::vector<idEntity>>& idEntities) const
{
	Vector2i start, end;

	if (lastDirection)
	{
		switch (lastDirection)
		{
		case NoneDirection:
			break;
		case Up:
			start.y = pos.y - viewLenght;
			start.x = pos.x;
			end.y = pos.y;
			end.x = pos.x + nTile.x;
			break;
		case Down:
			start.y = pos.y + nTile.y;
			start.x = pos.x;
			end.y = start.y + viewLenght;
			end.x = pos.x + nTile.x;
			break;
		case Right:
			start.y = pos.y;
			start.x = pos.x + nTile.x;
			end.y = pos.y + nTile.y;
			end.x = start.x + viewLenght;
			break;
		case Left:
			start.y = pos.y;
			start.x = pos.x - viewLenght;
			end.y = pos.y + nTile.y;
			end.x = pos.x;
			break;
		default:
			break;
		}
	}
	
	for (int j = start.y; j < end.y; j++)
	{
		for (int i = start.x; i < end.x; i++)
		{
			if (idEntities[j][i].typeEntity == TypeEntity::player)
			{
				return true;
			}
		}
	}

	return false;
}
//------------------------------------------------------------------------------------
//Enemy Class                                                                           
//------------------------------------------------------------------------------------