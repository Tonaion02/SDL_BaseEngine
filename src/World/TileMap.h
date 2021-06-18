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
	uint16_t m_width, m_height;
};





class UniqueTileLayer
{
public:
	UniqueTileLayer() {}
	UniqueTileLayer(const Vector2i& dimension);

	//Aggiungere tutte le liste di UniqueTile
	bool loadUniqueTileFromTemplate(const TemplateObject& templateObject, const Vector2i& pos, TileSetHandler& tileSetHandler);

public:
	std::vector<DestructbleTile> m_destructbleTiles;
	//std::vector<ChestTile> m_chestTiles;
	//std::vector<OpenableTile> m_openableTiles;

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

	uint16_t getMaxLayer() const;
	uint16_t getMaxWidth() const;
	uint16_t getMaxHeight() const;

	void reactTile(const Vector2i pos, int layer);

public:
	UniqueTileLayer m_uniqueTileLayer;

private:
	std::vector<TileLayer> m_tileLayers;
};