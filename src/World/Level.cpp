#include "Level.h"

#include "Format.h"

//Provvisorio
#include <iostream>





//------------------------------------------------------------------------------------
//Level Class
//------------------------------------------------------------------------------------
Level::Level(const std::string& filePathTileMap)
{
	std::vector<std::string> TileMapLines = getlines(filePathTileMap);

	//for (int i = 0; i < TileMapLines.size(); i++)
	//{
	//	SDL_Log(TileMapLines[i].c_str());
	//}

	std::string& line = TileMapLines[0];

	std::vector<std::vector<uint16_t>> bufferTiles;

	int currentNTileMap = -1;

	//Excract info from File
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
					std::string filePathTileSet;
					int firstVisualType;
					for (auto info : infoAboutTileSet)
					{
						if (isInString(info, "source="))
						{
							filePathTileSet = removeQuotationMarks(stride(line, "source="));
						}
						else if (isInString(info, "firstgid="))
						{
							firstVisualType = std::stoi(removeQuotationMarks(stride(line, "firstgid="))) - 1;
						}
					}
					//Search filePath of TileSet



					//Load a TileSet
					TileSet tileSet = TileSet("data/levels/" + filePathTileSet, firstVisualType, true);
					m_tileSetHandler.addTileSet(tileSet);
					//Load a TileSet
				}
				//Search TileSet and take info from tileset



				//Search a objectgroup(Object Layer)
				else if (isInString(line, "<objectgroup"))
				{
					line = removeFrontSpace(line);
					line = remove(line, ">");
					std::vector<std::string> infoAboutObjectgroup = split(line, " ");
					int choice=-1;

					//Excract info from intestation of ObjectGroup
					for (auto info : infoAboutObjectgroup)
					{
						if (isInString(info, "name="))
						{
							info = removeQuotationMarks(stride(info, "name="));
							//Controll if is a UniqueTileLayer
							if (info == "UniqueTile")
							{
								choice = 0;
							}
							//Controll if is a UniqueTileLayer

						}
					}
					//Excract info from intestation of ObjectGroup

					

					//Decide if you create a UniqueTileLayer or EnemyLayer or other
					i++;
					line = TileMapLines[i];
					if (choice == 0)
					{
						m_tileMaps[currentNTileMap].m_uniqueTileLayer = UniqueTileLayer({ m_width, m_height });
						
						while (!isInString(TileMapLines[i], "</objectgroup"))
						{
							line = TileMapLines[i];
							if (isInString(line, "<object"))
							{
								line = removeFrontSpace(line);
								//In base of presence of this "/" create two case, in the first the object is totaly equal to that in template, in other case is modified and search properties modified
								line = remove(line, "/");
								line = remove(line, ">");
								
								std::vector<std::string> infoAboutObject = split(line, " ");
								std::string filePathTemplate;
								Vector2i posObject = { 0, 0 };

								for (auto info : infoAboutObject)
								{
									if (isInString(info, "template="))
									{
										filePathTemplate = removeQuotationMarks(stride(info, "template="));
									}
									else if (isInString(info, "x="))
									{
										posObject.x = std::stoi(removeQuotationMarks(stride(info, "x="))) / m_tileWidth;
									}
									else if (isInString(info, "y="))
									{
										posObject.y = std::stoi(removeQuotationMarks(stride(info, "y="))) / m_tileHeight - 1;
									}
								}

								m_tileMaps[currentNTileMap].m_uniqueTileLayer.loadUniqueTileFromTemplate(filePathTemplate, posObject, m_tileSetHandler);
							}
							i++;
						}
					}
					//Decide if you create a UniqueTileLayer or EnemyLayer or other
				}
				//Search a objectgroup(Object Layer)



				//Search a new group and add a new TileMap
				//Ricordati di porre prima l'objectgroup
				else if (isInString(line, "<group"))
				{
					currentNTileMap++;
					m_tileMaps.push_back(TileMap());
				}
				//Search a new group and add a new TileMap



				//Search Layer and take info from layer
				else if (isInString(line, "<layer"))
				{
					//Avance the line
					i++;
					line = TileMapLines[i];
					i++;
					//Avance the line

					//Excract Layer
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
								workingLayer.m_tiles[j][index] = m_tileSetHandler.getTile(id);
							}
						}

						i++;
					}
					//Excract Layer



					//Add Layer to TileMap
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
	//Excract info from File



	//Construct Static Graphic Layer
	Surface temp;
	for (int i = 0; i < m_tileMaps.size(); i++)
	{
		for (int layer = 0; layer < m_tileMaps[i].getMaxLayer(); layer++)
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
						m_tileSetHandler.blitSurfaceTile(visualType, { x * m_tileWidth, y * m_tileHeight }, temp);
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
	//Construct Static Graphic Layer



	//Print to screen the tileMaps 
	for (int i = 0; i < m_tileMaps.size(); i++)
	{
		std::cout << std::endl << std::endl;
		for (int y = 0; y < m_height; y++)
		{
			std::string line = "";
			for (int x = 0; x < m_width; x++)
			{
				line += std::to_string(m_tileMaps[i].getCommonTile(x, y, 0).visualType).c_str();
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