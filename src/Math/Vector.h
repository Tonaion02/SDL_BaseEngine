#pragma once

#include "PrecompiledHeaders.h"




class Vector2i;

class Vector2f
{
public:
	Vector2f(float x = 0, float y = 0) :x(x), y(y) {}
	Vector2f(const Vector2i& other);

	Vector2f operator+(const Vector2f& other)
	{
		return Vector2f(this->x + other.x, this->y + other.y);
	}

	Vector2f operator-(const Vector2f& other)
	{
		return Vector2f(this->x - other.x, this->y - other.y);
	}

	float x, y;
};





class Vector2i
{
public:
	Vector2i(int32_t x = 0, int32_t y = 0) :x(x), y(y) {}
	Vector2i(const Vector2f& other) :x((int)other.x), y((int)other.y) {}

	Vector2i operator+(const Vector2i& other)
	{
		return Vector2i(this->x + other.x, this->y + other.y);
	}

	Vector2i operator-(const Vector2i& other)
	{
		return Vector2i(this->x - other.x, this->y - other.y);
	}

	int32_t x, y;
};
