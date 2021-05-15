#include "Level.h"

#include "Format.h"

//Provvisorio
#include <iostream>





//------------------------------------------------------------------------------------
//Level Class
//------------------------------------------------------------------------------------
Level::Level(const std::string& filePathTileMap)
{
	std::vector<std::string> TileSetLines;
	std::vector<std::string> TileMapLines = getlines(filePathTileMap);

	//for (int i = 0; i < TileMapLines.size(); i++)
	//{
	//	SDL_Log(TileMapLines[i].c_str());
	//}

	std::string& line = TileMapLines[0];

	std::vector<std::vector<uint16_t>> bufferTiles;
	
	std::vector<CommonTile> commonTileSet;

	Surface commonGraphicTileSet;
	int widthTileSet;
	int heightTileSet;
	int nTileSetX;
	int nTileSetY;

	int currentNTileMap = 0;
	m_tileMaps.push_back(TileMap());

	for (int i = 0; i < TileMapLines.size(); i++)
	{
		line = TileMapLines[i];
		//Search TileMap
		if (isInString(line, "<map"))
		{
			//Read and take info from the intestation of TileMap
			line = removeFrontSpace(line);
			std::vector<std::string> infoAboutMap = split(line, " ");
			for (auto info : infoAboutMap)
			{
				if (isInString(info, "tilewidth="))
				{
					m_tileWidth = std::stoi(removeQuotationMarks(stride(info, "tilewidth=")));
				}
				else if (isInString(info, "tileheight="))
				{
					m_tileHeight = std::stoi(removeQuotationMarks(stride(info, "tileheight=")));
				}
				else if (isInString(info, "width="))
				{
					m_width = std::stoi(removeQuotationMarks(stride(info, "width=")));
				}
				else if (isInString(info, "height="))
				{
					m_height = std::stoi(removeQuotationMarks(stride(info, "height=")));
				}
			}
			//Read and take info from the intestation of TileMap



			//Setting dimension of bufferTiles
			for (int j = 0; j < m_height; j++)
			{
				bufferTiles.push_back(std::vector<uint16_t>(m_width));
			}
			//Setting dimension of bufferTiles
			


			//Read and excract info from TileMap
			while (i < TileMapLines.size() && !isInString(line, "</map>"))
			{
				line = TileMapLines[i];
				
				
				
				//Search TileSet and take info from tileset
				if (isInString(line, "<tileset"))
				{
					//Search filePath of TileSet
					line = removeFrontSpace(line);
					line = remove(line, "/");
					line = remove(line, ">");
					std::vector<std::string> infoAboutTileSet = split(line, " ");
					for (auto info : infoAboutTileSet)
					{
						if (isInString(info, "source="))
						{
							m_filePathTileSet = removeQuotationMarks(stride(line, "source="));
						}
					}
					//Search filePath of TileSet



					//Load TileSet
					TileSetLines = getlines("data/levels/" + m_filePathTileSet);
					//Load TileSet



					//
					for (auto info : TileSetLines)
					{
						if (isInString(info, "<tileset"))
						{

						}
						else if (isInString(info, "<image"))
						{
							info = removeFrontSpace(info);
							info = remove(info, "/");
							info = remove(info, ">");
							std::string filePathImageCommonTileSet;
							std::vector<std::string> strings = split(info, " ");
							for (auto s : strings)
							{
								if (isInString(s, "source="))
								{
									filePathImageCommonTileSet = removeQuotationMarks(stride(s, "source="));
									commonGraphicTileSet = Surface("data/levels/" + filePathImageCommonTileSet);
								}
								else if (isInString(s, "width="))
								{
									widthTileSet = std::stoi(removeQuotationMarks(stride(s, "width=")));
								}
								else if (isInString(s, "height="))
								{
									heightTileSet = std::stoi(removeQuotationMarks(stride(s, "height=")));
								}
							}
						}
						else if (isInString(info,"<tile"))
						{
							info = removeFrontSpace(info);
							info = remove(info, "/");
							info = remove(info, ">");
							std::vector<std::string> infoAboutTile = split(info, " ");
							uint16_t visualType;
							RealType realType;

							for (auto inf : infoAboutTile)
							{
								if (isInString(inf, "id="))
								{
									visualType = std::stoi(removeQuotationMarks(stride(inf, "id=")));
								}
								else if (isInString(inf, "type="))
								{
									realType = (RealType)std::stoi(removeQuotationMarks(stride(inf, "type=")));
								}
							}
							commonTileSet.push_back(CommonTile(realType, visualType));
						}
					}
					//
				}
				//Search TileSet and take info from tileset



				//Search Layer and take info from layer
				else if (isInString(line, "<layer"))
				{
					//Excract info about layer
					line = removeFrontSpace(line);
					line = remove(line, ">");
					std::vector<std::string> infoAboutLayer = split(line, " ");
					std::string layerName;
					for (auto info : infoAboutLayer)
					{
						if (isInString(info, "name="))
						{
							layerName = removeQuotationMarks(stride(info, "name="));
						}
					}
					//Excract info about layer



					//Avance the line
					i++;
					line = TileMapLines[i];
					//Avance the line



					//Decide in base to layer info if i must create another tileMap to add
					//Layer0TileMap0
					//DA TESTARE
					if (isInString(layerName, "Layer"))
					{
						int indexForString = findInString(layerName, "TileMap");
						layerName = stride(layerName, indexForString, layerName.size());
						int nTileMap = std::stoi(stride(layerName, "TileMap"));
						if (nTileMap > currentNTileMap)
						{
							m_tileMaps.push_back(TileMap());
							currentNTileMap++;
						}
					}
					//Decide in base to layer info if i must create another tileMap to add



					//Excract Layer
					i++;
					TileLayer workingLayer = TileLayer(m_width, m_height);

					std::vector<std::string> bufferTilesCurrentLine;
					for (int j = 0; j < m_height; j++)
					{
						line = TileMapLines[i];
						line = removeFrontSpace(line);
						bufferTilesCurrentLine = split(line, ",");

						for (int index = 0; index < m_width; index++)
						{
							int id = std::stoi(bufferTilesCurrentLine[index]) - 1;
							if (id >= 0)
							{
								workingLayer.m_tiles[j][index] = commonTileSet[id];
							}
						}

						i++;
					}
					//Excract Layer



					//Add Layer to TileMap
					//Provissorio quella che è l'ingradimento in questa parte della tileMap, successivamente distinguere in base al nome quale è la tilemap di appartenenza
					m_tileMaps[currentNTileMap].addTileLayer(workingLayer);
					//Add Layer to TileMap
				}
				//Search Layer and take info from layer
				i++;
			}
			//Read and excract info from TileMap
		}
		//Search TileMap
	}



	//In testing
	nTileSetX = widthTileSet / m_tileWidth;
	nTileSetY = heightTileSet / m_tileHeight;
	Surface temp;
	for (int i = 0; i < m_tileMaps.size(); i++)
	{
		for(int layer = 0;layer < m_tileMaps[i].getMaxLayer();layer++)
		{
			temp = Surface(Color(0, 0, 0, 0), m_width * m_tileWidth, m_height * m_tileHeight);
			for (int y = 0; y < m_height; y++)
			{
				for (int x = 0; x < m_width; x++)
				{
					RealType realType = m_tileMaps[i].getCommonTile(x, y, layer).realType;
					if (realType > 0)
					{
						uint16_t visualType = m_tileMaps[i].getCommonTile(x, y, layer).visualType;
						int yTileSet = visualType / nTileSetX;
						int xTileSet = visualType - (yTileSet * nTileSetX);
						commonGraphicTileSet.blit({ x * m_tileWidth, y * m_tileHeight }, { xTileSet * m_tileWidth, yTileSet * m_tileHeight }, { m_tileWidth, m_tileHeight }, temp);
					}
				}
			}
			int necessityOfAnotherLayer = m_graphicLayer.size() - 1;
			if (necessityOfAnotherLayer < i)
			{
				m_graphicLayer.push_back(std::vector<Image>(0));
			}
			m_graphicLayer[i].push_back(Image(temp.getRawSurface()));
			temp.free();
		}
		
	}
	//In testing



	//Print to screen the tileMaps 
	for (int i = 0; i < m_tileMaps.size(); i++)
	{
		std::cout << std::endl << std::endl;
		for (int y = 0; y < m_height; y++)
		{
			std::string line = "";
			for (int x = 0; x < m_width; x++)
			{
				line += std::to_string(m_tileMaps[i].getCommonTile(x, y, 0).realType).c_str();
			}
			std::cout << line << std::endl;
		}
	}
	//Print to screen the tileMaps
}



uint16_t Level::getWidth()
{
	return m_width;
}



uint16_t Level::getHeight()
{
	return m_height;
}



uint16_t Level::getTileWidth()
{
	return m_tileWidth;
}



uint16_t Level::getTileHeight()
{
	return m_tileHeight;
}
//------------------------------------------------------------------------------------
//Level Class
//------------------------------------------------------------------------------------