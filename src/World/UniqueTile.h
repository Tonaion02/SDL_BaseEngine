#pragma once

#include "PrecompiledHeaders.h"
#include "Format.h"

#include "TemplateTiled.h"

#include "Graphic/Image.h"

#include "TileSet.h"

#include "Item/Item.h"





struct UniqueTile
{
	UniqueTile() {}
};





struct DestructbleTile : public UniqueTile
{
	DestructbleTile() :UniqueTile() {}
	DestructbleTile(const TemplateObject& templateObject, TileSetHandler& tileSetHandler);

	uint16_t getCurrentImage();

	bool isDestroyed;

	std::array<uint16_t, 2> idImages;
	std::string nameTileset;
};





struct ChestTile : public UniqueTile
{
	ChestTile() :UniqueTile() {}
	ChestTile(const TemplateObject& templateObject, TileSetHandler& tileSetHandler);

	uint16_t getCurrentImage();

	bool isOpened;

	std::string nameTileSet;
	std::array<uint16_t, 2> idImages;
};





struct OpenableTile : public UniqueTile
{
	OpenableTile() :UniqueTile() {}
	OpenableTile(const TemplateObject& templateObject, TileSetHandler& tileSetHandler);

	uint16_t getCurrentImage();

	bool isOpened;

	std::string nameTileSet;
	std::array<uint16_t, 2> idImages;
};





struct StairsTile : public UniqueTile
{
	StairsTile() : UniqueTile() {}
	StairsTile(const TemplateObject& templateObject, TileSetHandler& tileSetHandler);

	uint16_t z;

	std::string nameTileSet;
	uint16_t idImage;
	uint16_t direction;
};