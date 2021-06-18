#include "UniqueTile.h"





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