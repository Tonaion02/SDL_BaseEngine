#include "World.h"





//------------------------------------------------------------------------------------
//World Class
//------------------------------------------------------------------------------------
bool World::loadLevel(const std::string& filePath)
{
	s_indexLevels[filePath] = s_currentIndexLevels;
	s_currentIndexLevels++;
	s_levels.push_back(Level(filePath));
	return true;
}



uint16_t World::getIndexLevel(const std::string& filePath)
{
	//aggiungere assert per controllo
	return s_indexLevels[filePath];
}



Level& World::getLevel(int indexLevel)
{
	//aggiungere assert per indexLevel
	return s_levels[indexLevel];
}
//------------------------------------------------------------------------------------
//World Class
//------------------------------------------------------------------------------------