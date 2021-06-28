#pragma once

#include "PrecompiledHeaders.h"
#include "Format.h"

#include "Level.h"





class World
{
public:
	static World& get()
	{
		static World instance;
		return instance;
	}

	bool loadLevel(const std::string& filePath, TileSetHandler& tileSetHandler);
	uint16_t getIndexLevel(const std::string& filePath);
	Level& getLevel(int indexLevel);

protected:
	World() :s_currentIndexLevels(0) {}


protected:
	std::unordered_map<std::string, uint16_t> s_indexLevels;
	std::vector<Level> s_levels;

	uint16_t s_currentIndexLevels;
};