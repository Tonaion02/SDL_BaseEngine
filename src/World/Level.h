#pragma once

#include "TileMap.h"
#include "TileSet.h"
#include "Entity/EntityLayer.h"

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
	
	std::vector<TileMap> m_tileMaps;
	std::vector<EntityLayer> m_entityLayers;

	//FORSE VA RESO PRIVATO
	TileSetHandler m_tileSetHandler;

private:
	uint16_t m_width, m_height, m_maxZ;
	uint16_t m_tileWidth, m_tileHeight;
	std::string m_filePathTileMap;
	std::string m_filePathTileSet;

};
//Aggiungere le funzioni render layerTileMap e render objecLayerTileMap

//PUNTI FONDAMENTALI CREAZIONE DI UN LIVELLO
//-ORDINE DEI LAYER:
//		°TileLayer(functionality)
//		°UniqueTileLayer
//		°OtherLayer(No functionality)
//
//-STARE ATTENTI A STABILIRE I TYPE DI TUTTO IL TILESET, NON SOLAMENTE QUELLI CHE UTILIZZIAMO, MAGARI ANCHE SETTARLI SOLO COME 0, MA E' NECESSARIO STABILIRLO(IN FUTURO RIMUOVERE TALE OBBLIGO)
//
//-AGGIUNTA DI UN UNIQUETILE:
//		°Porre prima nel TileLayer(functionality) il tile con il giusto type
//		°Inserire solo successivamente un oggetto qualsiasi
//		°Aprire un template, .tx, e selezionando l'oggetto o gli oggetti rimpiazzare con template 