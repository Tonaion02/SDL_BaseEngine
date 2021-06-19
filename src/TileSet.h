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

	void blitImageTile(uint16_t visualType, const Vector2i& pos) const;
	void blitSurfaceTile(uint16_t visualType, const Vector2i& pos, Surface& other) const;

	bool isWithSurface() const;

	uint16_t getFirstVisualType() const;

	std::string getFilePath() const;

	CommonTile& getTile(int index);

	const Vector2i getTileDimension() const;
	uint16_t getColumns() const;

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

	void blitImageTile(uint16_t index, const std::string& nameTileSet, const Vector2i& pos) const;
	void blitSurfaceTile(uint16_t index, const std::string& nameTileSet, const Vector2i& pos, Surface& other) const;
	void blitImageTile(uint16_t visualType, const Vector2i& pos) const;
	void blitSurfaceTile(uint16_t visualType, const Vector2i& pos, Surface& other) const;

	const Vector2i getTileDimension();
	
	const TileSet& getTileSet(const std::string& nameTileSet) const;
private:
	std::vector<TileSet> m_tileSets;
};

//IMPORTANTE QUANDO SI CREA UN TILESET
//ANDARE A CAMBIARE IL TIPO DI TUTTI QUANTI I NUOVI TILE SETTANDOLI A 1