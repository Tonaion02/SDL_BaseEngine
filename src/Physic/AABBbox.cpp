#include "AABBbox.h"





//------------------------------------------------------------------------------------
//AABBbox Class                                                                           
//------------------------------------------------------------------------------------
AABBbox::AABBbox(const Vector2f& minPos, const Vector2i& dimension, float mass)
	:m_min(minPos), m_max(m_min + dimension), m_mass(mass)
{

}



void AABBbox::update(float deltaTime)
{

}



void AABBbox::computeForce(float deltaTime, const Vector2f& forceToCompute)
{
	Vector2f a = Vector2f(forceToCompute.x / m_mass, forceToCompute.y / m_mass);
	m_speed = Vector2f(deltaTime * a.x, deltaTime * a.y);
}



Vector2f AABBbox::getPosCenter() const
{
	return Vector2f((m_min.x + m_max.x) / 2.0f, (m_min.y + m_max.y) / 2.0f);
}



void AABBbox::moveX(float deltaTime)
{
	float space = m_speed.x * deltaTime;
	space = AABBbox::conversionFromMeterToPixel(space);
	m_min.x += space;
	m_max.x += space;
}



void AABBbox::moveY(float deltaTime)
{
	float space = m_speed.y * deltaTime;
	space = AABBbox::conversionFromMeterToPixel(space);
	m_min.y += space;
	m_max.y += space;
}



void AABBbox::move(float deltaTime)
{
	moveX(deltaTime);
	moveY(deltaTime);
}



bool AABBbox::detectionX(const AABBbox& other)
{
	return m_min.x < other.m_max.x && m_max.x > other.m_min.x;
}



bool AABBbox::detectionY(const AABBbox& other)
{
	return m_min.y < other.m_max.y && m_max.y > other.m_min.y;
}



bool AABBbox::detection(const AABBbox& other)
{
	return this->detectionX(other) && this->detectionY(other);
}



float AABBbox::conversionFromMeterToPixel(float distance)
{
	return distance / 0.0003f;
}
//------------------------------------------------------------------------------------
//AABBbox Class                                                                           
//------------------------------------------------------------------------------------