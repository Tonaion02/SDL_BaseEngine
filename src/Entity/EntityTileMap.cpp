#include "EntityTileMap.h"




//------------------------------------------------------------------------------------
//Entity Class
//------------------------------------------------------------------------------------
void Entity::move()
{
	return;
}



void Entity::startMove(Direction direction)
{
	if (direction != Direction::NoneDirection)
	{
		if (direction != lastDirection)
		{
			delayChangeDirection.start();
			lastDirection = direction;
		}

		else if (delayChangeDirection.isEnd())
		{
			lastDirection = currentDirection;
			currentDirection = direction;
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



bool Entity::controllMove(Direction direction, TileMap& tileMap, std::vector<std::vector<idEntity>> idEntities)
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
			Vector2i p = { t.x + i, t.y + j };
			
		}
	}
	//Controll if tile is occupied from another entity





	//CommonTile tile = tileMap.getCommonTile(t.x, t.y, 0);

	/*if (tile.isUnique())
	{
		switch (tile.realType)
		{
		case Destructble:
			if (!tileMap.m_uniqueTileLayer.m_destructbleTiles[tileMap.m_uniqueTileLayer.m_indexMatrix[t.y][t.x]].isDestroyed)
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
	}*/
	//Controllo vero e proprio

	return true;
}



void Entity::update(float deltaTime, TileMap& tileMap)
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
			if (controllMove(currentDirection, tileMap))
			{
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



void Entity::render(const Vector2i pos, const TileSetHandler& tileSetHandler)
{
	
}
//------------------------------------------------------------------------------------
//Entity Class
//------------------------------------------------------------------------------------