#include "Level.h"

#include "Format.h"

//Provvisorio
#include <iostream>





//------------------------------------------------------------------------------------
//Level Class
//------------------------------------------------------------------------------------
Level::Level(const std::string& filePathTileMap, TileSetHandler& entityTileSetHandler)
{
	std::vector<std::string> TileMapLines = getlines(filePathTileMap);

	std::string& line = TileMapLines[0];

	std::vector<std::vector<uint16_t>> bufferTiles;

	int currentNTileMap = -1;

	CacheTemplateObjectHandler cacheUniqueTileTemplates;

	CacheTemplateObjectHandler cacheEntities;

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
					line = remove(line, ">");
					//to remove only the last "/"
					line = stride(line, 0, line.size() - 1);
					//to remove only the last "/"
					std::vector<std::string> infoAboutTileSet = split(line, " ");
					std::string filePathTileSet;
					int firstVisualType;
					for (auto info : infoAboutTileSet)
					{
						if (isInString(info, "source="))
						{ 
							info = removeQuotationMarks(stride(info, "source="));
							filePathTileSet = stride(info, "../tileset/");
						}
						else if (isInString(info, "firstgid="))
						{
							firstVisualType = std::stoi(removeQuotationMarks(stride(line, "firstgid="))) - 1;
						}
					}
					//Search filePath of TileSet



					//Load a TileSet
					TileSet tileSet = TileSet("data/tileset/" + filePathTileSet, firstVisualType, true);
					m_tileSetHandler.addTileSet(tileSet);
					//Load a TileSet
				}
				//Search TileSet and take info from tileset



				//Search a objectgroup(Object Layer)
				else if (isInString(line, "<objectgroup"))
				{
					line = removeFrontSpace(line);
					if (!isInString(line, "/>"))
					{
						line = remove(line, ">");
						std::vector<std::string> infoAboutObjectgroup = split(line, " ");
						int choice = -1;

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

								//Controll if is a EntityLayer
								else if (info == "Entity")
								{
									choice = 1;
								}
								//Controll if is a EntityLayer

							}
						}
						//Excract info from intestation of ObjectGroup



						//Decide if you create a UniqueTileLayer or EnemyLayer or other
						i++;
						line = TileMapLines[i];

						//UniqueTileLayer Creation
						if (choice == 0)
						{
							m_tileMaps[currentNTileMap].m_uniqueTileLayer = UniqueTileLayer({ m_width, m_height });

							while (!isInString(TileMapLines[i], "</objectgroup"))
							{
								line = TileMapLines[i];
								if (isInString(line, "<object"))
								{
									bool modified = false;
									line = removeFrontSpace(line);
									//Controll if is a modified template searching "/"
									if (!isInString(line, "/"))
									{
										modified = true;
									}
									//Controll if is a modified template searching "/"

									//Search info about template
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
									//Search info about template

									//Load template and save in cache
									cacheUniqueTileTemplates.loadTemplateObject(filePathTemplate);
									TemplateObject templateObject = cacheUniqueTileTemplates.getTemplateObject(filePathTemplate);
									//Load template and save in cache

									//If is the template is modified charge changes
									if (modified)
									{
										while (!isInString(line, "</object"))
										{
											i++;
											line = TileMapLines[i];



											if (isInString(line, "<property"))
											{
												std::vector<std::string> infoAboutProperty = split(line, " ");

												Property property = Property(line);

												for (int l = 0; l < templateObject.properties.size(); l++)
												{
													if (templateObject.properties[l].name == property.name)
													{
														templateObject.properties[l].value = property.value;
													}
												}
											}
										}
									}
									//If is the template is modified charge changes

									//Load template in m_tileMaps
									m_tileMaps[currentNTileMap].m_uniqueTileLayer.loadUniqueTileFromTemplate(templateObject, posObject, m_tileSetHandler);
									//Load template in m_tileMaps
								}
								i++;
							}
						}
						//UniqueTileLayer Creation



						else if (choice == 1)
						{
							m_entityLayers.push_back(EntityLayer(m_width, m_height));

							while (!isInString(TileMapLines[i], "</objectgroup"))
							{
								line = TileMapLines[i];
								
								if (isInString(line, "<object"))
								{
									bool modified = false;
									line = removeFrontSpace(line);
									//Controll if is a modified template searching "/"
									if (!isInString(line, "/"))
									{
										modified = true;
									}
									//Controll if is a modified template searching "/"

									//Search info about template
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
									//Search info about template



									//Load template and save in cache
									cacheEntities.loadTemplateObject(filePathTemplate);
									TemplateObject templateObject = cacheEntities.getTemplateObject(filePathTemplate);
									//Load template and save in cache



									//If is the template is modified charge changes
									if (modified)
									{
										while (!isInString(line, "</object"))
										{
											i++;
											line = TileMapLines[i];



											if (isInString(line, "<property"))
											{
												std::vector<std::string> infoAboutProperty = split(line, " ");

												Property property = Property(line);

												for (int l = 0; l < templateObject.properties.size(); l++)
												{
													if (templateObject.properties[l].name == property.name)
													{
														templateObject.properties[l].value = property.value;
													}
												}
											}
										}
									}
									//If is the template is modified charge changes



									//Load entity from template
									m_entityLayers[currentNTileMap].loadEntityFromTemplate(templateObject, posObject, entityTileSetHandler);
									//Load entity from template
								}

								i++;
							}

						}
						//Decide if you create a UniqueTileLayer or EnemyLayer or other
					}


				}
				//Search a objectgroup(Object Layer)



				//Search a new group and add a new TileMap
				//Ricordati di porre prima l'objectgroup
				else if (isInString(line, "<group"))
				{
					currentNTileMap++;
					m_tileMaps.push_back(TileMap());
					m_entityLayers.push_back(EntityLayer(m_width, m_height));
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
					if (realType > 1)
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



	//Set some value
	m_maxZ = currentNTileMap;
	//da sostituire con lo specifico push_back() di un inizializzato EntityLayer
	//m_entityLayers = std::vector<EntityLayer>(m_maxZ);
	//Set some value



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



Image& Level::getGraphicLayer(uint16_t z, uint16_t z2)
{
	//Assert for z e z2
	//z for tileMaps
	//z2 for layer of one TileMap
	return m_graphicLayer[z][z2];
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