#include "GraphicTileSet.h"





//------------------------------------------------------------------------------
//GraphicTileSet Class
//------------------------------------------------------------------------------
GraphicTileSet::GraphicTileSet(const std::string& filePath, const Vector2i& tileDimension, bool withSurface)
	:m_filePath(filePath), m_image(Image(filePath)), m_withSurface(withSurface), m_tileDimension(tileDimension)
{
	if (m_withSurface)
	{
		m_surface = Surface(filePath);
	}

	m_columns = m_image.getW() / tileDimension.x;
}



void GraphicTileSet::blitTile(uint16_t visualType, const Vector2i& pos) const
{
	Vector2i posTileSetImage = { 0, visualType / m_columns };
	posTileSetImage.x = visualType - (posTileSetImage.y * m_columns);
	posTileSetImage = { posTileSetImage.x * m_tileDimension.x, posTileSetImage.y * m_tileDimension.y };
	m_image.blit(pos, posTileSetImage, m_tileDimension);
}



void GraphicTileSet::blitTileSurface(uint16_t visualType, const Vector2i& pos, Surface& other) const
{
	if (m_withSurface)
	{
		Vector2i posTileSetImage = { 0, visualType / m_columns };
		posTileSetImage.x = visualType - (posTileSetImage.y * m_columns);
		posTileSetImage = { posTileSetImage.x * m_tileDimension.x, posTileSetImage.y * m_tileDimension.y };
		m_surface.blit(pos, posTileSetImage, m_tileDimension, other);
	}
}



void GraphicTileSet::setAlpha(float alpha)
{
	m_image.setAlpha(alpha);
}
//------------------------------------------------------------------------------
//GraphicTileSet Class
//------------------------------------------------------------------------------





//------------------------------------------------------------------------------
//GraphicTileSetHandler Class
//------------------------------------------------------------------------------
void GraphicTileSetHandler::loadTileSet(const std::string& filePath, const Vector2i& tileDimension, bool withSurface)
{
	//Controllo filePath

	m_graphicTileSets[filePath] = new GraphicTileSet(filePath, tileDimension, withSurface);
}



void GraphicTileSetHandler::blitTile(const std::string& filePath, uint16_t visualType, const Vector2i& pos) const
{
	auto iter = m_graphicTileSets.find(filePath);
	if (iter != m_graphicTileSets.end())
	{
		(*iter).second->blitTile(visualType, pos);
	}
}



void GraphicTileSetHandler::blitTileSurface(const std::string& filePath, uint16_t visualType, const Vector2i& pos, Surface& other) const
{
	auto iter = m_graphicTileSets.find(filePath);
	if (iter != m_graphicTileSets.end())
	{
		if ((*iter).second->isWithSurface())
		{
			(*iter).second->blitTileSurface(visualType, pos, other);
		}
	}
}



void GraphicTileSetHandler::blitTile(const std::string& filePath, uint16_t visualType, const Vector2i& pos, float alpha) const
{
	auto iter = m_graphicTileSets.find(filePath);
	if (iter != m_graphicTileSets.end())
	{
		(*iter).second->setAlpha(alpha);
		(*iter).second->blitTile(visualType, pos);
		(*iter).second->setAlpha(1.0f);
	}
}
//------------------------------------------------------------------------------
//GraphicTileSetHandler Class
//------------------------------------------------------------------------------