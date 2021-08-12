#pragma once

#include "PrecompiledHeaders.h"

#include "Image.h"





class GraphicTileSet
{
public:
	GraphicTileSet() {}
	GraphicTileSet(const std::string& filePath, const Vector2i& tileDimension, bool withSurface = false);

	void blitTile(uint16_t visualType, const Vector2i& pos) const;
	void blitTileSurface(uint16_t visualType, const Vector2i& pos, Surface& other) const;

	bool isWithSurface() const { return m_withSurface; }
	std::string getFilePath() const { return m_filePath; }

	void setAlpha(float alpha);

private:
	Image m_image;
	Surface m_surface;
	bool m_withSurface;

	uint16_t m_columns;
	Vector2i m_tileDimension;

	std::string m_filePath;
};





class GraphicTileSetHandler
{
public:
	GraphicTileSetHandler() {}

	void loadTileSet(const std::string& filePath, const Vector2i& tileDimension, bool withSurface = false);

	void blitTile(const std::string& filePath, uint16_t visualType, const Vector2i& pos) const;
	void blitTileSurface(const std::string& filePath, uint16_t visualType, const Vector2i& pos, Surface& other) const;

	void blitTile(const std::string& filePath, uint16_t visualType, const Vector2i& pos, float alpha) const;

private:
	std::unordered_map<std::string, GraphicTileSet*> m_graphicTileSets;
};