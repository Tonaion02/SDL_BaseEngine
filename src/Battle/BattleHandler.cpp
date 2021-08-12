#include "Battle/BattleHandler.h"





//------------------------------------------------------------------------------------
//BattleHandler Class                                                                           
//------------------------------------------------------------------------------------
void BattleHandler::update(float deltaTime)
{
	//Update all rectangleParticles
	for (int i = 0; i < Categories::NCategories; i++)
	{
		for (auto& iter : s_rectangleParticles[i])
		{
			iter->update(deltaTime);
		}
	}

	for (auto& particle : s_rectangleParticles[Categories::Player])
	{
		RectangleParticle copy = *particle;
		particle->m_box.moveX(deltaTime);

		for (auto wall : s_staticRectangeWalls)
		{
			if (copy.m_box.detection(wall->m_box))
			{
				*particle = copy;
				break;
			}
		}

		copy = *particle;
		particle->m_box.moveY(deltaTime);

		for (auto wall : s_staticRectangeWalls)
		{
			if (copy.m_box.detection(wall->m_box))
			{
				*particle = copy;
				break;
			}
		}

		particle->m_pos = particle->m_box.m_min;
	}
	//Update all rectangleParticles
}



void BattleHandler::draw()
{
	//Draw all walls
	for (auto iter : s_staticRectangeWalls)
	{
		iter->draw(s_gTileSetHandler);
	}
	//Draw all walls



	//Draw all rectangleParticles
	for (int i = 0; i < Categories::NCategories; i++)
	{
		for (auto iter : s_rectangleParticles[i])
		{
			iter->draw(s_gTileSetHandler);
		}
	}
	//Draw all rectangleParticles
}



void BattleHandler::createRectangleEntity(Categories category)
{
	s_rectangleEntities[category].emplace_back(new RectangleEntity());
}



void BattleHandler::createRectangleParticle(float deltaTime, const std::string& filePath, const AABBbox& box, const Stats& stats, const Vector2f& forceToCompute, Categories category)
{
	s_rectangleParticles[category].emplace_back(new RectangleParticle(box, stats));
	s_rectangleParticles[category][s_rectangleParticles[category].size() - 1]->setNameTileSet(filePath);
	s_rectangleParticles[category][s_rectangleParticles[category].size() - 1]->m_pos = box.m_min;
	s_rectangleParticles[category][s_rectangleParticles[category].size() - 1]->m_box.computeForce(deltaTime, forceToCompute);
}



void BattleHandler::createStasticRectangleWalls(const std::string& filePath, const AABBbox& box, const Stats& stats)
{
	s_staticRectangeWalls.emplace_back(new StaticRectangleWall(box, stats));
	s_staticRectangeWalls[s_staticRectangeWalls.size() - 1]->setNameTileSet(filePath);
	s_staticRectangeWalls[s_staticRectangeWalls.size() - 1]->m_pos = box.m_min;
}



void BattleHandler::destroyDeadEntity()
{

}
//------------------------------------------------------------------------------------
//BattleHandler Class                                                                           
//------------------------------------------------------------------------------------