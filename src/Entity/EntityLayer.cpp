#include "Entity/EntityLayer.h"





//------------------------------------------------------------------------------------
//EntityLayer Class                                                                           
//------------------------------------------------------------------------------------
EntityLayer::EntityLayer(uint16_t width, uint16_t height)
	:m_width(width), m_height(height)
{
	for (int j = 0; j < height; j++)
	{
		m_idEntities.push_back(std::vector<idEntity>(width));
	}

	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			m_idEntities[y][x] = idEntity(TypeEntity::NoneTypeEntity, -1);
		}
	}
}



void EntityLayer::add(Npc& npc)
{
	m_npcs.push_back(npc);
	int index = m_npcs.size() - 1;

	for (int j = 0; j < npc.nTile.y; j++)
	{
		for (int i = 0; i < npc.nTile.x; i++)
		{
			Vector2i p = { npc.pos.x + i, npc.pos.y + j };
			m_idEntities[p.y][p.x] = idEntity(TypeEntity::npc, index);
		}
	}
}



void EntityLayer::add(Enemy& enemy)
{
	m_enemies.push_back(enemy);
	int index = m_enemies.size() - 1;

	for (int j = 0; j < enemy.nTile.y; j++)
	{
		for (int i = 0; i < enemy.nTile.x; i++)
		{
			Vector2i p = { enemy.pos.x + i, enemy.pos.y + j };
			m_idEntities[p.y][p.x] = idEntity(TypeEntity::enemy, index);
		}
	}
}



void EntityLayer::addPlayer(const Vector2i& posPlayer, const Vector2i& nTile)
{
	
	for (int j = 0; j < nTile.y; j++)
	{
		for (int i = 0; i < nTile.x; i++)
		{
			Vector2i p = { posPlayer.x + i, posPlayer.y + j };
			m_idEntities[p.y][p.x] = idEntity(TypeEntity::player, 0);
		}
	}
}
//------------------------------------------------------------------------------------
//EntityLayer Class                                                                           
//------------------------------------------------------------------------------------