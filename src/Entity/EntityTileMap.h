#pragma once

#include "PrecompiledHeaders.h"

#include "Math/Vector.h"

#include "World/TileMap.h"

#include "Animation/Animation.h"

#include "StatusHandler.h"

#include "Time/Delay.h"





enum TypeEntity
{
	NoneTypeEntity = -1,
	player,
	npc,
	enemy
};



struct idEntity
{
	idEntity() {}
	idEntity(TypeEntity type, uint16_t i) : typeEntity(type), index(i) {}

	TypeEntity typeEntity;
	uint16_t index;
};





enum Direction
{
	NoneDirection = -1,
	Up,
	Down,
	Right,
	Left
};



enum StatusMovement
{
	NoneStatusMovement = -1,
	Lock,
	InMovement
};



enum TypeTerrain
{
	NoneTypeTerrain = -1,
	Solid,
	Liquid
};



enum Velocity
{
	NoneVelocity = -1,
	Walking, 
	Running
};



struct Entity
{
public:
	Entity() 
		:lastDirection(Direction::Down), currentDirection(Direction::NoneDirection), 
		typeTerrain(TypeTerrain::Solid), statusMovement(StatusMovement::Lock), 
		delayChangeDirection(Delay(0.2f)), nTile({1, 2}), nameTileSet("playerTileSet16.tsx")
	{}

	virtual void move(Direction direction, std::vector<std::vector<idEntity>>& idEntities);
	virtual void startMove(Direction direction, TileMap& tileMap, std::vector<std::vector<idEntity>>& idEntities);
	virtual void updateDirection(Direction direction);
	virtual bool controllMove(Direction direction, TileMap& tileMap, const std::vector<std::vector<idEntity>>& idEntities);
	virtual bool controllPosition(const Vector2i& t, TileMap& tileMap, const std::vector<std::vector<idEntity>>& idEntities);
	virtual void update(float deltaTime, TileMap& tileMap, std::vector<std::vector<idEntity>>& idEntities);
	virtual uint16_t getIdImage();
	virtual void updateVelocity(Velocity velocity);
	virtual void updateSurface(TypeTerrain typeTerrain);
	virtual void render(const Vector2i& posInProspective, const TileSetHandler& tileSetHandler);

public:
	static bool isOccupied(const Vector2i& p, idEntity id, const std::vector<std::vector<idEntity>>& idEntities);
	static int getIndexEntity(const Vector2i& p, const std::vector<std::vector<idEntity>>& idEntities);
	static idEntity getIdEntity(const Vector2i& p, const std::vector<std::vector<idEntity>>& idEntities);

public:
	std::string name;

	Direction lastDirection;
	Direction currentDirection;

	StatusMovement statusMovement;
	TypeTerrain typeTerrain;
	Velocity velocity;

	Vector2i pos;
	uint16_t z;
	Vector2i posImage;
	
	Vector2i tileDimension;

	//PER IL FUTURO, serve per individuare il numero sulle x e sulle y di tile
	Vector2i nTile;

	std::string nameTileSet;
	std::vector<std::vector<std::vector<DinamicAnimation>>> animations; 
	std::vector<uint16_t> idStaticImage;

	Delay delayChangeDirection;
	//vector di animation

	bool rotateHitboxWithDirection=false;
};





struct Npc : public Entity
{
public:
	Npc() :Entity() {}
	Npc(const std::string& filePath);

public:

};





struct Enemy : public Entity
{
public:
	Enemy() :Entity() {}
	Enemy(const std::string& filePath);

	virtual bool detectPlayer(const std::vector<std::vector<idEntity>>& idEntities) const;
public:
	uint16_t viewLenght = 0;
};