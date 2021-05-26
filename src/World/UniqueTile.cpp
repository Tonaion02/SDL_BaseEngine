#include "UniqueTile.h"





DestructbleTile::DestructbleTile(const TemplateObject& templateObject, TileSetHandler& tileSetHandler)
	:UniqueTile()
{
	std::string nameTileSet;
	Vector2i tileDim = tileSetHandler.getTileDimension();

	for (int i = 0; i < templateObject.properties.size(); i++)
	{
		Property property = templateObject.properties[i];

		if (property.name == "destructed")
		{
			isDestroyed = fromStringToBool(property.value);
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
				Surface temp = Surface(Color(0, 0, 0, 0), tileDim.x, tileDim.y);
				tileSetHandler.blitSurfaceTile((uint16_t)std::stoi(infoAboutImages[j]), nameTileSet, { 0, 0 }, temp);
				images[j] = Image(temp.getRawSurface());
				temp.free();
			}
		}
	}
}





Image& DestructbleTile::getCurrentImage()
{
	if (isDestroyed)
	{
		return images[0];
	}
	return images[1];
}