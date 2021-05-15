#pragma once

#include "Math/Vector.h"
#include "Tile.h"





class TileLayer 
{
public:
	TileLayer() {}
	TileLayer(uint16_t width, uint16_t height);

	std::vector<std::vector<CommonTile>> m_tiles;
};





class UniqueTileLayer
{
public:
	UniqueTileLayer() {}

	//Aggiungere tutte le liste di UniqueTile
};





//First TileLayer is with functionality
//Second or more TileLayer is without functionality
class TileMap
{
public:
	TileMap() {}

	//Aggiungere getUniqueTile per ogni UniqueTile
	void addTileLayer(TileLayer& tileLayer);

	//Get Common Tile of a specific layer with x and y
	CommonTile& getCommonTile(int x, int y, int layer);

	uint16_t getMaxLayer();

private:
	std::vector<TileLayer> m_tileLayer;
	UniqueTileLayer m_uniqueTileLayer;
};