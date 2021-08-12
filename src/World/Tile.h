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
	Openable, //9
	Stairs, //10
	Transition //11
	//Respawning
};





struct CommonTile
{
	CommonTile() {}
	CommonTile(uint16_t realType, uint16_t visualType) 
		: realType((RealType)realType), visualType(visualType) 
	{}

	RealType realType;
	uint16_t visualType;

	bool isUnique() const
	{
		switch (realType)
		{
		case NoneTileRealType:
		case Void:
		case Graphic:
		case Obstacle:
		case Sea:
		case Ground:
			return false;

		case Destructble:
		case Chest:
		case Openable:
		case Stairs:
		case Transition:
			return true;
		}
	}

	bool isWalkable() const
	{
		switch (realType)
		{
		case Void:
		case Graphic:
		case Obstacle:
		case Sea:
		case Chest:
			return false;

		case Grass:
		case Ground:
		case Stairs:
		case Transition:
			return true;
		}
	}

	bool isSea() const
	{
		switch (realType)
		{
		case Sea:
			return true;
		default:
			return false;
		}
	}

	bool blockView() const
	{
		switch (realType)
		{
		case Void:
		case Graphic:
		case Ground:
		case Sea:
		case Chest:
		case Grass:
		case Transition:
			return false;

		case Obstacle:
		case Openable:
		case Stairs:
			return true;
		}
	}
};
