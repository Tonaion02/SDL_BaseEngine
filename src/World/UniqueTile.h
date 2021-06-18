#pragma once

#include "PrecompiledHeaders.h"
#include "Format.h"

#include "TemplateTiled.h"

#include "Graphic/Image.h"

#include "TileSet.h"





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

	bool isOpened;
};





struct OpenableTile : public UniqueTile
{
	OpenableTile() :UniqueTile() {}

	bool isOpened;
};