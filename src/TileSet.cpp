#include "TileSet.h"

#include "Format.h"





//------------------------------------------------------------------------------
//TileSet Class
//------------------------------------------------------------------------------
TileSet::TileSet(const std::string& filePath, uint16_t firstVisualType, bool withSurface)
	:m_filePath(filePath), m_withSurface(withSurface), m_firstVisualType(firstVisualType)
{
	//Load TileSet info from File
	std::vector<std::string> tileSetLines = getlines(filePath);
	//Load TileSet info from File



	//Init Variables
	std::string& line = tileSetLines[0];
	m_tileDimension = { 0,0 };
	//Init Variables



	//Excract info of TileSet from File
	for (int i = 0; i < tileSetLines.size(); i++)
	{
		//
		line = tileSetLines[i];



		//Search in File the tileset line
		if (isInString(line, "<tileset"))
		{
			line = removeFrontSpace(line);
			line = remove(line, ">");
			std::vector<std::string> infoTileSet = split(line, " ");
			
			for (auto info : infoTileSet)
			{
				if (isInString(info, "columns="))
				{
					m_columns = std::stoi(removeQuotationMarks(stride(info, "columns=")));
				}
				else if (isInString(info, "tilewidth="))
				{
					m_tileDimension.x = std::stoi(removeQuotationMarks(stride(info, "tilewidth=")));
				}
				else if (isInString(info, "tileheight="))
				{
					m_tileDimension.y = std::stoi(removeQuotationMarks(stride(info, "tileheight=")));
				}
			}
		}
		//Search in File the tileset line



		//Search in File the image line
		else if (isInString(line, "<image"))
		{
			line = removeFrontSpace(line);
			line = stride(line, 0, line.size() - 1);
			line = remove(line, ">");
			std::vector<std::string> infoImage = split(line, " ");
			for (auto info : infoImage)
			{
				if (isInString(info, "source="))
				{
					info = removeQuotationMarks(stride(info, "source="));
					
					//da migliorare
					info = stride(info, "../images/");

					m_image = Image("data/images/" + info);
					if (withSurface)
					{
						m_surface = Surface("data/images/" + info);
					}
				}
			}
		}
		//Search in File the image line



		//Search in File tile
		else if (isInString(line, "<tile"))
		{
			line = removeFrontSpace(line);
			line = remove(line, "/");
			line = remove(line, ">");
			std::vector<std::string> infoTile = split(line, " ");
			
			RealType realType;
			uint16_t visualType;
			for (auto info : infoTile)
			{
				if (isInString(info, "id="))
				{
					visualType = std::stoi(removeQuotationMarks(stride(info, "id="))) + firstVisualType;
				}
				else if (isInString(info, "type="))
				{
					realType = (RealType)std::stoi(removeQuotationMarks((stride(info, "type="))));
				}
			}

			m_tiles.push_back(CommonTile(realType, visualType));
		}
		//Search in File tile
	}
	//Excract info of TileSet from File
}



Image TileSet::getImage()
{
	return m_image;
}



Surface TileSet::getSurface()
{
	if (m_withSurface)
	{
		return m_surface;
	}
}



void TileSet::blitImageTile(uint16_t visualType, const Vector2i& pos) const
{
	Vector2i posTileSetImage = {0, visualType / m_columns};
	posTileSetImage.x = visualType - (posTileSetImage.y * m_columns);
	posTileSetImage = { posTileSetImage.x * m_tileDimension.x, posTileSetImage.y * m_tileDimension.y };
	m_image.blit(pos, posTileSetImage, m_tileDimension);
}



void TileSet::blitSurfaceTile(uint16_t visualType, const Vector2i& pos, Surface& other) const
{
	if (m_withSurface)
	{
		Vector2i posTileSetImage = { 0, visualType / m_columns };
		posTileSetImage.x = visualType - (posTileSetImage.y * m_columns);
		posTileSetImage = { posTileSetImage.x * m_tileDimension.x, posTileSetImage.y * m_tileDimension.y };
		m_surface.blit(pos, posTileSetImage, m_tileDimension, other);
	}
}



bool TileSet::isWithSurface() const
{
	return m_withSurface;
}



uint16_t TileSet::getFirstVisualType() const
{
	return m_firstVisualType;
}



std::string TileSet::getFilePath() const
{
	return m_filePath;
}



CommonTile& TileSet::getTile(int index)
{
	return m_tiles[index];
}



const Vector2i TileSet::getTileDimension() const
{
	return m_tileDimension;
}



uint16_t TileSet::getColumns() const
{
	return m_columns;
}
//------------------------------------------------------------------------------
//TileSet Class
//------------------------------------------------------------------------------





//------------------------------------------------------------------------------
//TileSetHandler Class
//------------------------------------------------------------------------------
void TileSetHandler::addTileSet(TileSet& tileSet)
{
	m_tileSets.push_back(tileSet);
}



void TileSetHandler::blitImageTile(uint16_t index, const std::string& nameTileSet, const Vector2i& pos) const
{
	int j = 0;
	for (int i = 0; i < m_tileSets.size(); i++)
	{
		if (isInString(m_tileSets[i].getFilePath(), nameTileSet))
		{
			j = i;
			break;
		}
	}

	m_tileSets[j].blitImageTile(index, pos);
}



void TileSetHandler::blitSurfaceTile(uint16_t index, const std::string& nameTileSet, const Vector2i& pos, Surface& other) const
{
	int j = 0;
	for (int i = 0; i < m_tileSets.size(); i++)
	{
		if (isInString(m_tileSets[i].getFilePath(), nameTileSet))
		{
			j = i;
			break;
		}
	}

	m_tileSets[j].blitSurfaceTile(index, pos, other);
}



void TileSetHandler::blitImageTile(uint16_t visualType, const Vector2i& pos) const
{
	int j = 0;
	for (int i = 0; i < m_tileSets.size(); i++)
	{
		if (visualType <= m_tileSets[i].getFirstVisualType())
		{
			break;
		}
		j = i;
	}

	m_tileSets[j].blitImageTile(visualType - m_tileSets[j].getFirstVisualType(), pos);
}



void TileSetHandler::blitSurfaceTile(uint16_t visualType, const Vector2i& pos, Surface& other) const
{
	int j = 0;
	for (int i = 0; i < m_tileSets.size(); i++)
	{
		if (visualType < m_tileSets[i].getFirstVisualType())
		{
			break;
		}
		j = i;
	}

	if (m_tileSets[j].isWithSurface())
	{
		m_tileSets[j].blitSurfaceTile(visualType - m_tileSets[j].getFirstVisualType(), pos, other);
	}
}



CommonTile& TileSetHandler::getTile(int index)
{
	int j = 0;
	for (int i = 0; i < m_tileSets.size(); i++)
	{
		if (index < m_tileSets[i].getFirstVisualType())
		{
			break;
		}
		j = i;
	}


	return m_tileSets[j].getTile(index - m_tileSets[j].getFirstVisualType());
}



CommonTile& TileSetHandler::getTile(int index, const std::string& nameTileSet)
{
	int j = 0;
	for (int i = 0; i < m_tileSets.size(); i++)
	{
		if (isInString(m_tileSets[i].getFilePath(), nameTileSet))
		{
			j = i;
			break;
		}
	}

	return m_tileSets[j].getTile(index);
}



const Vector2i TileSetHandler::getTileDimension()
{
	return m_tileSets[0].getTileDimension();
}



const TileSet& TileSetHandler::getTileSet(const std::string& nameTileSet) const
{
	for (int i = 0; i < m_tileSets.size(); i++)
	{
		if (isInString(m_tileSets[i].getFilePath(), nameTileSet))
		{
			return m_tileSets[i];
		}
	}

	//aggiungere assert se non trova niente
}
//------------------------------------------------------------------------------
//TileSetHandler Class
//------------------------------------------------------------------------------