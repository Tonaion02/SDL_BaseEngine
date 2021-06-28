#pragma once

#include "PrecompiledHeaders.h"

#include "Entity/EntityTileMap.h"





enum PlayerActivity
{
	NonePlayerActivity = -1,
	PlayerExploring,
	PlayerFighting,
	PlayerInteracting,
	PlayerDialoging
};



enum TypeInteraction
{
	NoneTypeInteraction = -1,
	WithTile,
	WithNpc
};



struct Interaction
{
	//Vector2i pos;
	std::vector<Vector2i> poses;
	TypeInteraction typeInteraction;
};



struct Player : public Entity
{
public:
	Player() :currentActivity(PlayerActivity::PlayerExploring) {}
	Player(const std::string& filePath);

	virtual void updateActivity(PlayerActivity activity);
	virtual void updatePlayer(float deltaTime, TileMap& tileMap, std::vector<std::vector<idEntity>>& idEntities);
	virtual void tryToInteract(const TileMap& tileMap, const std::vector<std::vector<idEntity>>& idEntities);
	virtual void react(TileMap& tileMap) override;
	virtual void deReact(TileMap& tileMap) override;
	virtual void renderPlayer(const Vector2i& posInProspective, const TileSetHandler& tileSetHandler) const;
	virtual void resetInteraction();
public:
	PlayerActivity currentActivity;

	StaticAnimation interactiveAnimation;

	Interaction interaction;

	uint16_t lastZ;

	bool changingLevel=false;
	Delay delayChangingLevel;
};