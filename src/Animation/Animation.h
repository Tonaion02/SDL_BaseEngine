#pragma once

#include "PrecompiledHeaders.h"

#include "General/Options.h"
#include "Math/Vector.h"
#include "Graphic/Image.h"





class Animation
{
public:
	Animation() {}

	virtual void start() {}
	virtual void animate(float deltaTime) {}
	virtual bool isEnd() { return !m_running; }

protected:
	bool m_running = false;
};





class StaticAnimation : public Animation
{
	friend Animation;
public:
	StaticAnimation() {}
	StaticAnimation(const std::vector<uint16_t>& idImages, const std::string& nameTileSet, float time, const Vector2i& pos);

	void start() override;
	void animate(float deltaTime) override;

	void loop();
	bool isLoop();
	uint16_t getIdImage();

	Vector2i getPos();

protected:
	Vector2i m_pos;

	float m_time = 1.0f;
	float m_index = 0.0f;
	float m_incrementIndex = 0.0f;

	//std::vector<Image> m_images;
	std::vector<uint16_t> m_idImages;
	std::string m_nameTileSet;

	bool m_loop = false;
};





class DinamicAnimation : public StaticAnimation
{
	friend StaticAnimation;
public:
	DinamicAnimation() : StaticAnimation() {}
	DinamicAnimation(const std::vector<uint16_t>& idImages, const std::string& nameTileSet, float time, const Vector2i& pos, float timeMoving, const Vector2i& spaceMove);

	void animate(float deltaTime) override;
	void start() override;

	void setPos(const Vector2i pos);

protected:
	float m_timeMoving = 0.0f;
	float m_timePassed = 0.0f;

	Vector2f m_posf;
	Vector2i m_spaceMove;
	Vector2f m_spaceIncrement;
	Vector2i m_end;
};