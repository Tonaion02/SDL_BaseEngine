#pragma once

#include "PrecompiledHeaders.h"

#include "Math/Vector.h"





struct AABBbox
{
public:
	AABBbox() {}
	AABBbox(const Vector2f& minPos, const Vector2i& dimension, float mass);

	void update(float deltaTime);

	void computeForce(float deltaTime, const Vector2f& forceToCompute);

	void moveX(float deltaTime);
	void moveY(float deltaTime);
	void move(float deltaTime);

	bool detectionX(const AABBbox& other);
	bool detectionY(const AABBbox& other);
	bool detection(const AABBbox& other);

	void setSpeed(const Vector2f& speed) { m_speed = speed; }
	Vector2f getSpeed() const { return m_speed; }
	Vector2f getMin() const { return m_min; }
	Vector2f getMax() const { return m_max; }
	Vector2f getPosCenter() const ;

	static float conversionFromMeterToPixel(float distance);

public:
	Vector2f m_min, m_max;

	float m_mass;
	Vector2f m_speed;
};