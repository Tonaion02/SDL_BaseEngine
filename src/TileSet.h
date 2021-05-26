#pragma once

#include "PrecompiledHeaders.h"

#include "World/Tile.h"

#include "Graphic/Image.h"





class TileSet
{
public:
	TileSet() {}
	TileSet(const std::string& filePath, uint16_t firstVisualType, bool withSurface=false);

	Image getImage();
	Surface getSurface();

	void blitImageTile(uint16_t visualType, const Vector2i& pos);
	void blitSurfaceTile(uint16_t visualType, const Vector2i& pos, Surface& other);

	bool isWithSurface();

	uint16_t getFirstVisualType();

	std::string getFilePath();

	CommonTile& getTile(int index);

	const Vector2i getTileDimension();

private:
	uint16_t m_columns;

	std::vector<CommonTile> m_tiles;
	
	Image m_image;
	Surface m_surface;
	bool m_withSurface;

	Vector2i m_tileDimension;

	std::string m_filePath;

	//IMPORTANT
	uint16_t m_firstVisualType;
};





class TileSetHandler
{
public:
	TileSetHandler() {}

	//Add TileSet
	void addTileSet(TileSet& tileSet);

	CommonTile& getTile(int index);
	CommonTile& getTile(int index, const std::string& nameTileSet);

	void blitImageTile(uint16_t index, const std::string& nameTileSet, const Vector2i& pos);
	void blitSurfaceTile(uint16_t index, const std::string& nameTileSet, const Vector2i& pos, Surface& other);
	void blitImageTile(uint16_t visualType, const Vector2i& pos);
	void blitSurfaceTile(uint16_t visualType, const Vector2i& pos, Surface& other);

	const Vector2i getTileDimension();
private:
	std::vector<TileSet> m_tileSets;
};
