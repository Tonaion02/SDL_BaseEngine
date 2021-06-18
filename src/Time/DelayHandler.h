#pragma once

#include "PrecompiledHeaders.h"





class FrameLimiter
{
public:
	static FrameLimiter& get()
	{
		static FrameLimiter instance;
		return instance;
	}

protected:
	FrameLimiter() : s_TickCounts(0) {}

	void update();
	float getDeltaTime();

protected:
	uint32_t s_TickCounts;
	float s_deltaTime;
};