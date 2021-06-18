#pragma once

#include "PrecompiledHeaders.h"





class Delay
{
public:
	Delay() {}
	Delay(float timeDelay)
		:m_timeDelay(timeDelay)
	{
		m_timePassed = m_timeDelay;
	}

	bool isEnd() const
	{
		return m_timePassed >= m_timeDelay;
	}

	void start()
	{
		m_timePassed = 0.0f;
	}

	void update(float deltaTime)
	{
		m_timePassed += deltaTime;
	}

	void terminate()
	{
		m_timePassed = m_timeDelay;
	}

private:
	float m_timeDelay = 0.0f;
	float m_timePassed = 0.0f;
};