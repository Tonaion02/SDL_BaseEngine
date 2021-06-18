#include "Entity/EntityLayer.h"





EntityLayer::EntityLayer(uint16_t width, uint16_t height)
	:m_width(width), m_height(height)
{
	for (int j = 0; j < height; j++)
	{
		m_idEntities.push_back(std::vector<idEntity>(width));
	}

	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			m_idEntities[y][x] = idEntity(TypeEntity::NoneTypeEntity, -1);
		}
	}
}