#pragma once

#include "Math/Vector.h"
#include "Format.h"

#include "Tile.h"

#include "UniqueTile.h"






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
	UniqueTileLayer(const Vector2i& dimension);

	//Aggiungere tutte le liste di UniqueTile

	bool loadUniqueTileFromTemplate(const std::string& nameTemplate, const Vector2i& pos, TileSetHandler& tileSetHandler);
public:
	//temporaneamente un std::vector
	std::vector<DestructbleTile> m_destructbleTiles;
	std::vector<Vector2i> m_pos;

	std::vector<std::vector<uint16_t>> m_indexMatrix;

private:
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

public:
	UniqueTileLayer m_uniqueTileLayer;

private:
	std::vector<TileLayer> m_tileLayer;
};