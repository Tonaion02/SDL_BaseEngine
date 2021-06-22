#include "Animation.h"





//------------------------------------------------------------------------------------
//StaticAnimation Class
//------------------------------------------------------------------------------------
StaticAnimation::StaticAnimation(const std::vector<uint16_t>& idImages, const std::string& nameTileSet, float time, const Vector2i& pos)
	:m_pos(pos), m_nameTileSet(nameTileSet), m_time(time), m_idImages(idImages)
{
	m_incrementIndex = m_idImages.size() / (m_time * 1000.0f);
}

void StaticAnimation::animate(float deltaTime)
{
	if (m_running)
	{
		m_index += m_incrementIndex * (deltaTime * 1000.0f);
		if (m_index >= m_idImages.size())
		{
			m_index = 0.0f;
			if (!m_loop)
			{
				m_running = false;
			}
		}
	}
}

uint16_t StaticAnimation::getIdImage() const
{
	return m_idImages[(int)m_index];
}

Vector2i StaticAnimation::getPos()
{
	return m_pos;
}

void StaticAnimation::start()
{
	m_index = 0.0f;
	m_running = true;
}

void StaticAnimation::loop()
{
	m_loop = !m_loop;
}

bool StaticAnimation::isLoop()
{
	return m_loop;
}

void StaticAnimation::setPos(const Vector2i& pos)
{
	m_pos = pos;
}
//------------------------------------------------------------------------------------
//StaticAnimation Class
//------------------------------------------------------------------------------------





//------------------------------------------------------------------------------------
//DinamicAnimation Class
//------------------------------------------------------------------------------------
DinamicAnimation::DinamicAnimation(const std::vector<uint16_t>& idImages, const std::string& nameTileSet, float time, const Vector2i& pos, float timeMoving, const Vector2i& spaceMove)
	:StaticAnimation(idImages, nameTileSet, time, pos), m_timeMoving(timeMoving), m_posf({ (float)pos.x, (float)pos.y }), m_spaceMove(spaceMove)
{
	//m_spaceIncrement.x = m_spaceMove.x / ((m_timeMoving / fileNames.size()) * Options::getFps());
	//m_spaceIncrement.y = m_spaceMove.y / ((m_timeMoving / fileNames.size()) * Options::getFps());

	m_spaceIncrement.x = m_spaceMove.x / (m_timeMoving);
	m_spaceIncrement.y = m_spaceMove.y / (m_timeMoving);

	m_loop = true;
}

void DinamicAnimation::animate(float deltaTime)
{
	if (m_running)
	{
		m_index += m_incrementIndex * deltaTime;

		if (m_index >= m_idImages.size())
		{
			if (m_loop)
			{
				m_index = 0.0f;
			}
			else
			{
				m_index = m_idImages.size() - 1;
			}
		}

		m_posf.x += m_spaceIncrement.x * deltaTime;
		m_posf.y += m_spaceIncrement.y * deltaTime;
		m_pos.x = (int)m_posf.x;
		m_pos.y = (int)m_posf.y;

		//if ((int)std::round(m_posf.x) == m_end.x && (int)std::round(m_posf.y) == m_end.y)
		//{
		//	m_running = false;
		//	m_pos = m_end;
		//	m_index = m_idImages.size() - 1;
		//}

		m_timePassed += deltaTime;
		if (m_timePassed >= m_timeMoving)
		{
			m_running = false;
			m_pos = m_end;
			m_index = m_idImages.size() - 1;
			m_timePassed = 0.0f;
		}

	}
}

void DinamicAnimation::start()
{
	m_index = 0.0f;
	m_running = true;
	//m_pos.x = pos.x * Options::getTileWidht();
	//m_pos.y = pos.y * Options::getTileHeight();
	m_posf.x = m_pos.x;
	m_posf.y = m_pos.y;
	m_end.x = m_pos.x + m_spaceMove.x;
	m_end.y = m_pos.y + m_spaceMove.y;
}

void DinamicAnimation::setPos(const Vector2i pos)
{
	m_pos = pos;
}
//------------------------------------------------------------------------------------
//DinamicAnimation Class
//------------------------------------------------------------------------------------