#pragma once

#include "TileMap.h"
#include "Graphic/Image.h"





class Level
{
public:
	Level() {}
	Level(const std::string& filePathTileMap);

	uint16_t getWidth();
	uint16_t getHeight();
	uint16_t getTileWidth();
	uint16_t getTileHeight();

public:
	std::vector<std::vector<Image>> m_graphicLayer;
	
private:
	std::vector<TileMap> m_tileMaps;
	
	uint16_t m_width, m_height, m_maxZ;
	uint16_t m_tileWidth, m_tileHeight;
	std::string m_filePathTileMap;
	std::string m_filePathTileSet;
};
//Probabilmente bisogna aggiungere la tileWidth e tileHeight

//PUNTI FONDAMENTALI CREAZIONE DI UN LIVELLO
//-STARE ATTENTI AI NOMI CHE SI UTILIZZANO PER I VARI LAYER, IN PARTICOLARE AL NUMERO DELLA TILEMAP AL QUALE FARE RIFERIMENTO
//-STARE ATTENTI A STABILIRE I TYPE DI TUTTO IL TILESET, NON SOLAMENTE QUELLI CHE UTILIZZIAMO, MAGARI ANCHE SETTARLI SOLO COME 0, MA E' NECESSARIO STABILIRLO(IN FUTURO RIMUOVERE TALE OBBLIGO)