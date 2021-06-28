#include "EntityTileMap.h"





Direction reverseDirection(Direction direction)
{
	switch (direction)
	{
	case Up:
		return Direction::Down;
	case Down:
		return Direction::Up;
	case Right:
		return Direction::Left;
	case Left:
		return Direction::Right;
	}
}



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
			if (delayChangeDirection.isEnd())
			{
				delayChangeDirection.start();

				bool canRotate = true;

				//Aggiungere controllo se può ruotare o meno

				if (rotateHitboxWithDirection)
				{
					if (
						((lastDirection == Direction::Down || lastDirection == Direction::Up) && (direction == Direction::Left || direction == Direction::Right)) 
						|| 
						((lastDirection == Direction::Left || lastDirection == Direction::Right) && (direction == Direction::Down || direction == Direction::Up)))
					{
						idEntity id = getIdEntity(pos, idEntities);

						nTile = { nTile.y, nTile.x };

						canRotate = controllPosition(pos, tileMap, idEntities);

						nTile = { nTile.y, nTile.x };

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
			
		}

		else 
		{
			if (delayChangeDirection.isEnd())
			{
				updateDirection(direction);
			}
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



bool Entity::controllPosition(const Vector2i& t, const TileMap& tileMap, const std::vector<std::vector<idEntity>>& idEntities) const
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
				case Chest:
					return false;
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



bool Entity::controllMove(Direction direction, const TileMap& tileMap,const std::vector<std::vector<idEntity>>& idEntities) const
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
				lastPos = pos;

				move(currentDirection, idEntities);
				
				deReact(tileMap);

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



	//Ho cambiato qua
	if (statusMovement == StatusMovement::InMovement)
	{
		if (!animations[typeTerrain][velocity][currentDirection].isEnd())
		{
			animations[typeTerrain][velocity][currentDirection].animate(deltaTime);
			posImage = animations[typeTerrain][velocity][currentDirection].getPos();
		}

		else if (animations[typeTerrain][velocity][currentDirection].isEnd())
		{
			statusMovement = StatusMovement::Lock;
			updateDirection(Direction::NoneDirection);

			posImage = { pos.x * tileDimension.x,pos.y * tileDimension.y };

			react(tileMap);
		}
	}

}



uint16_t Entity::getIdImage() const
{	
	if (statusMovement == StatusMovement::Lock)
	{
		return idStaticImage[lastDirection];
	}
	else if (statusMovement == StatusMovement::InMovement)
	{
		return animations[typeTerrain][velocity][currentDirection].getIdImage();
	}
}



void Entity::react(TileMap& tileMap)
{
	CommonTile commonTile = tileMap.getCommonTile(pos.x, pos.y, 0);

	if(commonTile.isUnique())
	{
		switch (commonTile.realType)
		{
		case Grass:
			return;

		case Sea:
			return;

		case Stairs:
			return;

		default:
			return;
		}
	}
}



void Entity::deReact(TileMap& tileMap)
{

}



void Entity::render(const Vector2i& posInProspective, const TileSetHandler& tileSetHandler) const
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
Npc::Npc(const std::string& nameEntity)
{

}



void Npc::updateNpc(float deltaTime, TileMap& tileMap, std::vector<std::vector<idEntity>>& idEntities)
{
	//Update rest of Npc
	update(deltaTime, tileMap, idEntities);
	//Update rest of Npc
}



void Npc::renderNpc(const Vector2i& posInProspective, const TileSetHandler& tileSetHandler) const
{
	render(posInProspective, tileSetHandler);
}
//------------------------------------------------------------------------------------
//Npc Class                                                                           
//------------------------------------------------------------------------------------




//------------------------------------------------------------------------------------
//Route Class                                                                           
//------------------------------------------------------------------------------------
Route::Route(const std::vector<Direction>& steps)
	:steps(steps), inverted(false), currentStep(0)
{

}



void Route::reverse()
{
	inverted = !inverted;
}



void Route::update()
{
	if (!inverted)
	{
		currentStep++;
	}
	else
	{
		currentStep--;
	}

	if (currentStep < 0)
	{
		reverse();
		currentStep = 0;
	}
	else if(currentStep >= steps.size())
	{
		reverse();
		currentStep = steps.size() - 1;
	}
}



Direction Route::getCurrentDirection() const
{
	if (!inverted)
	{
		return steps[currentStep];
	}
	else
	{
		return reverseDirection(steps[currentStep]);
	}
}
//------------------------------------------------------------------------------------
//Route Class                                                                           
//------------------------------------------------------------------------------------





//------------------------------------------------------------------------------------
//Enemy Class                                                                           
//------------------------------------------------------------------------------------
Enemy::Enemy(const std::string& nameEntity)
{
	std::string filePath = "data/entity/enemy/" + nameEntity;

	XMLobject xmlObject = XMLobject(filePath);

	for (int i = 0; i < xmlObject.xmlVariabs.size(); i++)
	{
		XMLvariab var = xmlObject.xmlVariabs[i];

		if (var.name == "nTile")
		{
			std::vector<std::string> splitter = split(var.getValue("value"), ",");
			nTile = { std::stoi(splitter[0]), std::stoi(splitter[1]) };
		}
	}
}



bool Enemy::detectPlayer(const TileMap& tileMap, const std::vector<std::vector<idEntity>>& idEntities) const
{
	Vector2i start, end;

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

	//controlla se sono valori validi start e end
	if (start.x < 0)
	{
		start.x = 0;
	}
	else if (start.x >= tileMap.getMaxWidth())
	{
		start.x = tileMap.getMaxWidth() - 1;
	}
	else if (start.y < 0)
	{
		start.y = 0;
	}
	else if(start.y >= tileMap.getMaxHeight())
	{
		start.y = tileMap.getMaxHeight() - 1;
	}
	else if (end.x < 0)
	{
		end.x = 0;
	}
	else if (end.x >= tileMap.getMaxWidth())
	{
		end.x = tileMap.getMaxWidth() - 1;
	}
	else if (end.y < 0)
	{
		end.y = 0;
	}
	else if (end.y >= tileMap.getMaxHeight())
	{
		end.y = tileMap.getMaxHeight() - 1;
	}
	//controlla se sono valori validi start e end



	for (int j = start.y; j < end.y; j++)
	{
		for (int i = start.x; i < end.x; i++)
		{
			if (idEntities[j][i].typeEntity == TypeEntity::player)
			{
				Vector2i startControll, endControll;

				switch (lastDirection)
				{
				case Up:
				case Down:
					startControll.y = j;
					endControll.y = end.y;
					startControll.x = i;
					endControll.x = i+1;
					break;
				case Right:
				case Left:
					startControll.y = j;
					endControll.y = j+1;
					startControll.x = i;
					endControll.x = end.x;
					break;
				}

				bool valid = true;

				for (int y = start.y; y < end.y; y++)
				{
					for (int x = start.x; x < end.x; x++)
					{
						CommonTile tile = tileMap.getCommonTile(x, y, z);
						if (!tile.isUnique())
						{
							valid = !tile.blockView();
						}
						else
						{
							//aggiungere parte per UniqueTile
						}

						if (!valid)
						{
							return false;
						}
					}
				}

				if (valid)
				{
					return true;
				}
			}
		}
	}

	return false;
}



void Enemy::takeDecision(float deltaTime, TileMap& tileMap, std::vector<std::vector<idEntity>>& idEntities)
{
	if (statusFighting == StatusFighting::Alive)
	{
		if (currentActivity == ActivityEnemy::Exploring)
		{
			//Moving part
			if (!stop)
			{
				if (statusMovement == StatusMovement::Lock)
				{
					if (!delayNextStep.isEnd())
					{
						delayNextStep.update(deltaTime);
					}
					//decides if must change direction or similar things
					//verify if he moves in base route or random direction
					if (withRoute)
					{
						if (delayChangeDirection.isEnd() && delayNextStep.isEnd())
						{
							if (controllMove(route.getCurrentDirection(), tileMap, idEntities))
							{
								startMove(route.getCurrentDirection(), tileMap, idEntities);
								route.update();
								delayNextStep.start();
							}
						}
					}
					else
					{
						//da fare
					}
					//verify if he moves in base route or random direction
					//decides if must change direction or similar things
				}
			}
			//Moving part
		}
	}
}



void Enemy::updateEnemy(float deltaTime, TileMap& tileMap, std::vector<std::vector<idEntity>>& idEntities)
{
	if (statusFighting == StatusFighting::Alive)
	{
		if (currentActivity == ActivityEnemy::Allerting && statusMovement == StatusMovement::Lock)
		{
			if (!allertingAnimation.isEnd())
			{
				allertingAnimation.animate(deltaTime);
			}

			if (allertingAnimation.isEnd())
			{
				currentActivity = ActivityEnemy::Fighting;
			}
		}
	}

	//update the rest of Enemy
	update(deltaTime, tileMap, idEntities);
	//update the rest of Enemy
}



void Enemy::startBattle()
{
	//function to start battle

	//function to start battle
}



Direction Enemy::decideMovement(const TileMap& tileMap, const std::vector<std::vector<idEntity>>& idEntities)
{
	Direction d;
	std::vector<Direction> bannedDirections;

	bool isNotGood = true;
	while (isNotGood)
	{
		d = Direction(std::rand() % 4);

		isNotGood = !controllMove(d, tileMap, idEntities);

		if (isNotGood)
		{
			for (int i = 0; i < bannedDirections.size(); i++)
			{
				if (bannedDirections[i] == d)
				{
					continue;
				}
			}
			bannedDirections.push_back(d);
			if (bannedDirections.size() == 4)
			{
				return Direction::NoneDirection;
			}
		}
		else
		{
			return d;
		}
	}

	return Direction::NoneDirection;
}



void Enemy::renderEnemy(const Vector2i& posInProspective, const TileSetHandler& tileSetHandler) const
{
	render(posInProspective, tileSetHandler);

	if (currentActivity == ActivityEnemy::Allerting)
	{
		Vector2i p = { posInProspective.x, posInProspective.y - tileDimension.y };
		tileSetHandler.getTileSet(nameTileSet).blitImageTile(allertingAnimation.getIdImage(), p);
	}
}



void Enemy::endBattle()
{

}
//------------------------------------------------------------------------------------
//Enemy Class                                                                           
//------------------------------------------------------------------------------------