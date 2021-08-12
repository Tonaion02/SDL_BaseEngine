#pragma once

#include "PrecompiledHeaders.h"

#include "Graphic/GraphicTileSet.h"

#include "Battle/GameObject.h"




class BattleInfo;

class BattleHandler
{
public:
	enum Categories
	{
		Neutral,
		Enemy,
		Player,
		NCategories = 3
	};

public:
	static BattleHandler& get()
	{
		static BattleHandler instance;
		return instance;
	}
	
	void loadBattle(const std::vector<BattleInfo>& battleInfos);

	void update(float deltaTime);
	void draw();

	void createRectangleEntity(Categories category);
	void createRectangleParticle(float deltaTime, const std::string& filePath, const AABBbox& box, const Stats& stats, const Vector2f& forceToCompute, Categories category);
	void createStasticRectangleWalls(const std::string& filePath, const AABBbox& box, const Stats& stats);

	void destroyDeadEntity();

protected:
	BattleHandler() : s_firstBattle(true) {}

public:
	GraphicTileSetHandler s_gTileSetHandler;

	bool s_firstBattle;

protected:
	std::vector<StaticRectangleWall*> s_staticRectangeWalls;

	std::array<std::vector<RectangleParticle*>, Categories::NCategories> s_rectangleParticles;

	std::array<std::vector<RectangleEntity*>, Categories::NCategories> s_rectangleEntities;


};