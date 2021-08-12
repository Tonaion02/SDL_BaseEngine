#include "UniqueTile.h"





//------------------------------------------------------------------------------------
//DestructbleTile Struct
//------------------------------------------------------------------------------------
DestructbleTile::DestructbleTile(const TemplateObject& templateObject, TileSetHandler& tileSetHandler)
	:UniqueTile()
{
	Vector2i tileDim = tileSetHandler.getTileDimension();

	Property property;
	//Load property from templateObject
	for (int i = 0; i < templateObject.properties.size(); i++)
	{
		property = templateObject.properties[i];

		if (property.name == "destructed")
		{
			isDestroyed = fromStringToBool(property.value);
		}
		else if (property.name == "tileset")
		{
			nameTileset = property.value;
		}
		else if (property.name == "images")
		{
			std::vector<std::string> infoAboutImages = split(property.value, ",");
			
			for (int j = 0; j < infoAboutImages.size(); j++)
			{
				idImages[j] = (uint16_t)std::stoi(infoAboutImages[j]);
			}
		}
	}
	//Load property from templateObject
}





uint16_t DestructbleTile::getCurrentImage()
{
	//Decide in base to isDestroyed what image load
	if (isDestroyed)
	{
		return idImages[0];
	}
	return idImages[1];
	//Decide in base to isDestroyed what image load
}
//------------------------------------------------------------------------------------
//DestructbleTile Struct
//------------------------------------------------------------------------------------





//------------------------------------------------------------------------------------
//OpenableTile Struct
//------------------------------------------------------------------------------------
OpenableTile::OpenableTile(const TemplateObject& templateObject, TileSetHandler& tileSetHandler)
{
	Vector2i tileDim = tileSetHandler.getTileDimension();

	Property property;
	//Load property from templateObject
	for (int i = 0; i < templateObject.properties.size(); i++)
	{
		property = templateObject.properties[i];

		if (property.name == "opened")
		{
			isOpened = fromStringToBool(property.value);
		}
		else if (property.name == "tileset")
		{
			nameTileSet = property.value;
		}
		else if (property.name == "images")
		{
			std::vector<std::string> infoAboutImages = split(property.value, ",");

			for (int j = 0; j < infoAboutImages.size(); j++)
			{
				idImages[j] = (uint16_t)std::stoi(infoAboutImages[j]);
			}
		}
	}
	//Load property from templateObject
}



uint16_t OpenableTile::getCurrentImage()
{
	if (isOpened)
	{
		return idImages[0];
	}
	return idImages[1];
}
//------------------------------------------------------------------------------------
//OpenableTile Struct
//------------------------------------------------------------------------------------





//------------------------------------------------------------------------------------
//ChestTile Struct
//------------------------------------------------------------------------------------
ChestTile::ChestTile(const TemplateObject& templateObject, TileSetHandler& tileSetHandler)
{
	Vector2i tileDim = tileSetHandler.getTileDimension();

	Property property;
	//Load property from templateObject
	for (int i = 0; i < templateObject.properties.size(); i++)
	{
		property = templateObject.properties[i];

		if (property.name == "opened")
		{
			isOpened = fromStringToBool(property.value);
		}
		else if (property.name == "tileset")
		{
			nameTileSet = property.value;
		}
		else if (property.name == "images")
		{
			std::vector<std::string> infoAboutImages = split(property.value, ",");

			for (int j = 0; j < infoAboutImages.size(); j++)
			{
				idImages[j] = (uint16_t)std::stoi(infoAboutImages[j]);
			}
		}
	}
	//Load property from templateObject
}



uint16_t ChestTile::getCurrentImage()
{
	//Decide in base to isDestroyed what image load
	if (isOpened)
	{
		return idImages[0];
	}
	return idImages[1];
	//Decide in base to isDestroyed what image load
}
//------------------------------------------------------------------------------------
//ChestTile Struct
//------------------------------------------------------------------------------------





//------------------------------------------------------------------------------------
//StairsTile Struct
//------------------------------------------------------------------------------------
StairsTile::StairsTile(const TemplateObject& templateObject, TileSetHandler& tileSetHandler)
{
	Vector2i tileDim = tileSetHandler.getTileDimension();

	Property property;
	//Load property from templateObject
	for (int i = 0; i < templateObject.properties.size(); i++)
	{
		property = templateObject.properties[i];

		if (property.name == "z")
		{
			z = std::stoi(property.value);
		}
		else if (property.name == "tileset")
		{
			nameTileSet = property.value;
		}
		else if (property.name == "images")
		{
			idImage = std::stoi(property.value);
		}
		else if(property.name == "direction")
		{
			direction = std::stoi(property.value);
		}
	}
	//Load property from templateObject
}
//------------------------------------------------------------------------------------
//StairsTile Struct
//------------------------------------------------------------------------------------





//------------------------------------------------------------------------------------
//TransitionTile Struct
//------------------------------------------------------------------------------------
TransitionTile::TransitionTile(const TemplateObject& templateObject, TileSetHandler& tileSetHandler)
{
	Vector2i tileDim = tileSetHandler.getTileDimension();

	Property property;
	//Load property from templateObject
	for (int i = 0; i < templateObject.properties.size(); i++)
	{
		property = templateObject.properties[i];

		if (property.name == "nextLevelZ")
		{
			nextLevelZ = std::stoi(property.value);
		}
		else if (property.name == "tileset")
		{
			nameTileSet = property.value;
		}
		else if (property.name == "images")
		{
			idImage = std::stoi(property.value);
		}
		else if (property.name == "nextLevelPos")
		{
			std::vector<std::string> infoAboutLevelPos = split(property.value, ",");
			nextLevelPos.x = std::stoi(infoAboutLevelPos[0]);
			nextLevelPos.y = std::stoi(infoAboutLevelPos[1]);
		}
		else if (property.name == "nameLevel")
		{
			nameLevel = property.value;
		}
	}
	//Load property from templateObject
}
//------------------------------------------------------------------------------------
//TransitionTile Struct
//------------------------------------------------------------------------------------