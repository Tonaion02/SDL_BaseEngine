#pragma once

#include "PrecompiledHeaders.h"

#include "Graphic/Image.h"





//Sostituire void con ground
enum RealType
{
	NoneTileRealType = 0,
	Void, //1
	Graphic, //2
	Ground, //3
	Obstacle, //4
	Sea, //5
	Grass, //6
	Destructble, //7
	Chest, //8
	Openable //9
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
		case Sea:
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
		case Sea:
		case Chest:
			return false;

		case Void:
		case Grass:
			return true;
		}
	}

	bool isSea()
	{
		switch (realType)
		{
		case NoneTileRealType:
		case Void:
		case Obstacle:
		case Chest:
			return false;

		case Sea:
		case Grass:
			return true;
		}
	}
};
