#include "GameObject.h"
#include "BattleHandler.h"





//------------------------------------------------------------------------------------
//GameObject Class                                                                           
//------------------------------------------------------------------------------------
void GameObject::update(float deltaTime)
{

}



void GameObject::draw(const GraphicTileSetHandler& gTileSetHandler)
{
	gTileSetHandler.blitTile(m_nameTileSet, m_currentImage, m_pos);
}
//------------------------------------------------------------------------------------
//GameObject Class                                                                           
//------------------------------------------------------------------------------------





//------------------------------------------------------------------------------------
//Stats Class                                                                           
//------------------------------------------------------------------------------------
Stats::Stats(float life, float attack, float def)
	:m_life(life), m_attack(attack), m_def(def)
{

}
//------------------------------------------------------------------------------------
//Stats Class                                                                           
//------------------------------------------------------------------------------------





//------------------------------------------------------------------------------------
//Entity Class                                                                           
//------------------------------------------------------------------------------------
BattleEntity::BattleEntity(const AABBbox& box, const Stats& stats)
	:m_box(box), m_currentStats(stats), m_maxStats(stats), GameObject()
{

}



void BattleEntity::update(float deltaTime)
{

}



void BattleEntity::takeDamage(const std::array<float, Type::NType>& rawDamage)
{
	m_currentStats.setLife(m_currentStats.getLife() - rawDamage[0]);
}



void BattleEntity::takeDamage(float rawDamage)
{
	m_currentStats.setLife(m_currentStats.getLife() - rawDamage);
}



void BattleEntity::draw(const GraphicTileSetHandler& gTileSetHandler)
{
	gTileSetHandler.blitTile(getNameTileSet(), m_currentImage, (Vector2i)m_box.m_min);
}



void BattleEntity::resetStats()
{
	m_currentStats = m_maxStats;
}



void BattleEntity::move(float deltaTime)
{
	
}
//------------------------------------------------------------------------------------
//Entity Class                                                                           
//------------------------------------------------------------------------------------





//------------------------------------------------------------------------------------
//StaticRectangleWall Class                                                                           
//------------------------------------------------------------------------------------
StaticRectangleWall::StaticRectangleWall(const AABBbox& box, const Stats& stats)
	:BattleEntity(box, stats)
{

}



void StaticRectangleWall::update(float deltaTime)
{

}



void StaticRectangleWall::takeDamage(float rawDamage)
{

}
//------------------------------------------------------------------------------------
//StaticRectangleWall Class                                                                           
//------------------------------------------------------------------------------------





//------------------------------------------------------------------------------------
//RectangleParticles Class                                                                           
//------------------------------------------------------------------------------------
RectangleParticle::RectangleParticle(const AABBbox& box, const Stats& stats)
	:BattleEntity(box, stats)
{

}



void RectangleParticle::update(float deltaTime)
{
	m_currentStats.setLife(m_currentStats.getLife() - deltaTime);
}



void RectangleParticle::draw(const GraphicTileSetHandler& gTileSetHandler)
{
	float alpha = m_currentStats.getLife() / m_maxStats.getLife();
	gTileSetHandler.blitTile(m_nameTileSet, m_currentImage, m_pos, alpha);
}



void RectangleParticle::move(float deltaTime)
{

}
//------------------------------------------------------------------------------------
//RectangleParticles Class                                                                           
//------------------------------------------------------------------------------------