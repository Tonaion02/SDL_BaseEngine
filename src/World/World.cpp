#include "World.h"





//------------------------------------------------------------------------------------
//World Class
//------------------------------------------------------------------------------------
bool World::loadLevel(const std::string& nameLevel, TileSetHandler& tileSetHandler)
{
	s_indexLevels[nameLevel] = s_currentIndexLevels;
	s_currentIndexLevels++;
	s_levels.push_back(Level("data/levels/" + nameLevel, tileSetHandler));
	return true;
}



uint16_t World::getIndexLevel(const std::string& nameLevel)
{
	//aggiungere assert per controllo
	return s_indexLevels[nameLevel];
}



Level& World::getLevel(int indexLevel)
{
	//aggiungere assert per indexLevel
	return s_levels[indexLevel];
}
//------------------------------------------------------------------------------------
//World Class
//------------------------------------------------------------------------------------