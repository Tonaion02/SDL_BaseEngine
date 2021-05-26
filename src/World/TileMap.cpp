#include "TileMap.h"





//------------------------------------------------------------------------------------
//TileLayer Class
//------------------------------------------------------------------------------------
TileLayer::TileLayer(uint16_t width, uint16_t height)
{
	for (int i = 0; i < height; i++)
	{
		m_tiles.push_back(std::vector<CommonTile>(width));
		for (int j = 0; j < width; j++)
		{
			m_tiles[i][j] = CommonTile(0, 0);
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





bool UniqueTileLayer::loadUniqueTileFromTemplate(const std::string& nameTemplate, const Vector2i& pos, TileSetHandler& tileSetHandler)
{
	std::vector<std::string> templateLines = getlines("data/levels/" + nameTemplate);
	std::string& line = templateLines[0];

	TemplateObject templateObject;
	//Set name in base at name of template
	templateObject.name = nameTemplate;

	for (int i = 0; i < templateLines.size(); i++)
	{
		line = templateLines[i];

		if (isInString(line, "<property"))
		{
			line = removeFrontSpace(line);
			line = remove(line, "/");
			line = remove(line, ">");

			std::vector<std::string> propertyInfo = split(line, " ");

			Property property;

			for (int j = 0; j < propertyInfo.size(); j++)
			{
				std::string& info = propertyInfo[j];
				if (isInString(info, "name="))
				{
					property.name = removeQuotationMarks(stride(info, "name="));
				}
				else if (isInString(info, "type="))
				{
					property.type = removeQuotationMarks(stride(info, "type="));
				}
				else if (isInString(info, "value="))
				{
					property.value = removeQuotationMarks(stride(info, "value="));
				}
			}

			templateObject.properties.push_back(property);
		}

		
	}

	RealType realType;

	for (int i = 0; i < templateObject.properties.size(); i++)
	{
		if (templateObject.properties[i].name == "UniqueTileType")
		{
			realType = (RealType)std::stoi(templateObject.properties[i].value);
		}
	}

	switch (realType)
	{
	case Destructble:
		m_destructbleTiles.push_back(DestructbleTile(templateObject, tileSetHandler));
		//Add pos, ricordati di andare a modificare quello che è il valore dividendolo per la dimensione del tile
		//m_pos.push_back(pos);
		m_indexMatrix[pos.y][pos.x] = m_destructbleTiles.size() - 1;
		break;
	case Chest:
		break;
	case Openable:
		break;
	default:
		break;
	}

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
	m_tileLayer.push_back(tileLayer);
}



CommonTile& TileMap::getCommonTile(int x, int y, int layer)
{
	return m_tileLayer[layer].m_tiles[y][x];
}



uint16_t TileMap::getMaxLayer()
{
	return m_tileLayer.size();
}
//------------------------------------------------------------------------------------
//TileMap Class
//------------------------------------------------------------------------------------