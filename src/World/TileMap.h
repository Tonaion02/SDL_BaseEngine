#pragma once

#include "Math/Vector.h"
#include "Tile.h"





class TileMap
{
public:
	TileMap() {}
	TileMap(uint16_t width, uint16_t height);

	CommonTile& getTile(int y, int x);

private:
	std::vector<std::vector<CommonTile>> m_tiles;

	uint16_t m_width, m_height;
};