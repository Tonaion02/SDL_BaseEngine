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

	Image& getCurrentImage();

	bool isDestroyed;

	Image images[2];
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