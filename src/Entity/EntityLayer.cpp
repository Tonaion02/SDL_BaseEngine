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



void EntityLayer::add(Npc& npc, TileSetHandler& tileSetHandler)
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



void EntityLayer::add(Enemy& enemy, TileSetHandler& tileSetHandler)
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



bool EntityLayer::loadEntityFromTemplate(const TemplateObject& templateObject, const Vector2i& pos, TileSetHandler& tileSetHandler)
{
	//Load Entity from Template

	TypeEntity typeEntity;
	std::string nameEntity;

	//Search the properties that reppresent the type of Entity
	for (int i = 0; i < templateObject.properties.size(); i++)
	{
		if (templateObject.properties[i].name == "TypeEntity")
		{
			typeEntity = (TypeEntity)std::stoi(templateObject.properties[i].value);
		}
		else if (templateObject.properties[i].name == "nameEntity")
		{
			nameEntity = templateObject.properties[i].value;
		}
	}
	//Search the properties that reppresent the type of Entity

	//Decide in base to the type of Entity what Entity create
	switch (typeEntity)
	{
	case NoneTypeEntity:
	{
		return false;
		break;
	}

	case player:
	{
		return false;
		break;
	}
	case npc:
	{
		Npc npc = Npc(nameEntity, tileSetHandler);
		npc.pos = pos;
		add(npc, tileSetHandler);
		break;
	}

	case enemy:
	{
		Enemy enemy = Enemy(nameEntity, tileSetHandler);
		enemy.pos = pos;
		enemy.posImage = { pos.x * enemy.tileDimension.x, pos.y * enemy.tileDimension.y };
		enemy.lastPos = pos;
		enemy.currentActivity = ActivityEnemy::Exploring;
		enemy.statusFighting = StatusFighting::Alive;

		add(enemy, tileSetHandler);
		break;
	}

	}
	//Decide in base to the type of Entity what Entity create

	return true;
	//Load Entity from Template
}
//------------------------------------------------------------------------------------
//EntityLayer Class                                                                           
//------------------------------------------------------------------------------------