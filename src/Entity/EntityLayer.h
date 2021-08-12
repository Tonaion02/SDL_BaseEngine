#pragma once

#include "PrecompiledHeaders.h"

#include "TileSet.h"
#include "Entity/EntityTileMap.h"





class EntityLayer
{
public:
	EntityLayer() {}
	EntityLayer(uint16_t width, uint16_t height);

	void add(Npc& npc, TileSetHandler& tileSetHandler);
	void add(Enemy& enemy, TileSetHandler& tileSetHandler);

	void addPlayer(const Vector2i& posPlayer, const Vector2i& nTile);

	bool loadEntityFromTemplate(const TemplateObject& templateObject, const Vector2i& pos, TileSetHandler& tileSetHandler);

public:
	TileSetHandler m_tileSetHandler;

	std::vector<Npc> m_npcs;
	std::vector<Enemy> m_enemies;
	std::vector<std::vector<idEntity>> m_idEntities;

private:
	
	
	//Probabilmente vector per ogni, tipo come per gli UniqueTiles

	uint16_t m_width, m_height;
};