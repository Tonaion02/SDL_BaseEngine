#include "TileMap.h"





//------------------------------------------------------------------------------------
//TileLayer Class
//------------------------------------------------------------------------------------
TileLayer::TileLayer(uint16_t width, uint16_t height)
	:m_width(width), m_height(height)
{
	for (int i = 0; i < height; i++)
	{
		m_tiles.push_back(std::vector<CommonTile>(width));
		for (int j = 0; j < width; j++)
		{
			m_tiles[i][j] = CommonTile(1, 0);
		}
	}
}
//------------------------------------------------------------------------------------
//TileLayer Class
//------------------------------------------------------------------------------------





//------------------------------------------------------------------------------------
//UniqueTileLayer Class
//------------------------------------------------------------------------------------
UniqueTileLayer::UniqueTileLayer(const Vector2i& dimension)
{
	for (int i = 0; i < dimension.y; i++)
	{
		m_indexMatrix.push_back(std::vector<uint16_t>(dimension.x));
	}
}





bool UniqueTileLayer::loadUniqueTileFromTemplate(const TemplateObject& templateObject, const Vector2i& pos, TileSetHandler& tileSetHandler)
{
	RealType realType;

	//Search the properties that reppresent the type of UniqueTile
	for (int i = 0; i < templateObject.properties.size(); i++)
	{
		if (templateObject.properties[i].name == "UniqueTileType")
		{
			realType = (RealType)std::stoi(templateObject.properties[i].value);
		}
	}
	//Search the properties that reppresent the type of UniqueTile

	//Decide in base to the type of UniqueTile what UniqueTile create
	switch (realType)
	{
	case Destructble:
		m_destructbleTiles.push_back(DestructbleTile(templateObject, tileSetHandler));
		m_indexMatrix[pos.y][pos.x] = m_destructbleTiles.size() - 1;
		break;
	case Chest:
		break;
	case Openable:
		break;
	default:
		break;
	}
	//Decide in base to the type of UniqueTile what UniqueTile create

	return true;
}
//------------------------------------------------------------------------------------
//UniqueTileLayer Class
//------------------------------------------------------------------------------------





//------------------------------------------------------------------------------------
//TileMap Class
//------------------------------------------------------------------------------------
void TileMap::addTileLayer(TileLayer& tileLayer)
{
	m_tileLayers.push_back(tileLayer);
}




void TileMap::reactTile(const Vector2i pos, int layer)
{
	if (m_tileLayers[layer].m_tiles[pos.y][pos.x].isUnique())
	{

	}
}



CommonTile& TileMap::getCommonTile(int x, int y, int layer)
{
	//CommonTile tile = m_tileLayers[layer].m_tiles[y][x];
	return m_tileLayers[layer].m_tiles[y][x];
}



CommonTile TileMap::getCommonTile(int x, int y, int layer) const
{
	return m_tileLayers[layer].m_tiles[y][x];
}



uint16_t TileMap::getMaxLayer() const
{
	return m_tileLayers.size();
}



uint16_t TileMap::getMaxWidth() const
{
	return m_tileLayers[0].m_width;
}



uint16_t TileMap::getMaxHeight() const
{
	return m_tileLayers[0].m_height;
}
//------------------------------------------------------------------------------------
//TileMap Class
//------------------------------------------------------------------------------------