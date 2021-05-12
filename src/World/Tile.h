#pragma once

#include "PrecompiledHeaders.h"





//Sostituire void con ground
enum RealType
{
	NoneTileRealType = -1,
	Void,
	Obstacle,
	Surfable,
	Destructble,
	Chest,
	Openable,
	Grass
};





struct CommonTile
{
	CommonTile() {}
	CommonTile(uint16_t realType, uint16_t visualType) 
		: realType((RealType)realType), visualType(visualType) 
	{}

	RealType realType;
	uint16_t visualType;

	bool isUnique() 
	{
		switch (realType)
		{
		case NoneTileRealType:
		case Void:
		case Obstacle:
		case Surfable:
			return false;

		case Destructble:
		case Chest:
		case Openable:
			return true;
		}
	}

	bool isWalkable()
	{
		switch (realType)
		{
		case Obstacle:
		case Surfable:
		case Chest:
			return false;

		case Void:
		case Grass:
			return true;
		}
	}

	bool isSurfable()
	{
		switch (realType)
		{
		case NoneTileRealType:
		case Void:
		case Obstacle:
		case Chest:
			return false;

		case Surfable:
		case Grass:
			return true;
		}
	}
};





struct UniqueTile
{
	UniqueTile() {}
};





struct DestructbleTile : public UniqueTile
{
	DestructbleTile() :UniqueTile() {}

	bool isDestroyed;
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