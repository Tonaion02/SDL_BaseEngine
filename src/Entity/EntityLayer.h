#pragma once

#include "PrecompiledHeaders.h"

#include "TileSet.h"
#include "Entity/EntityTileMap.h"





class EntityLayer
{
public:
	EntityLayer() {}
	EntityLayer(uint16_t width, uint16_t height);

	void add(const Npc& npc);
	void add(const Enemy& enemy);

	TileSetHandler m_tileSetHandler;

private:
	std::vector<std::vector<idEntity>> m_idEntities;
	
	//Probabilmente vector per ogni, tipo come per gli UniqueTiles
	std::vector<Npc> m_npcs;
	std::vector<Enemy> m_enemies;


	uint16_t m_width, m_height;
};