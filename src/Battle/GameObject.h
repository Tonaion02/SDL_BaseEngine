#pragma once

#include "PrecompiledHeaders.h"

#include "Math/Vector.h"

#include "Graphic/Image.h"
#include "Graphic/GraphicTileSet.h"

#include "Physic/AABBbox.h"





struct GameObject
{
public:
	GameObject() : m_pos(Vector2f(0.0f, 0.0f)), m_currentImage(0) {}

	virtual void update(float deltaTime);
	virtual void draw(const GraphicTileSetHandler& gTileSetHandler);

	//Vector2f getPos() { return m_pos; }
	//void setPos(const Vector2f& pos) { m_pos = pos; }
	std::string getNameTileSet() { return m_nameTileSet; }
	void setNameTileSet(const std::string& nameTileSet) { m_nameTileSet = nameTileSet; }

public:
	Vector2f m_pos;
	int m_currentImage;

protected:
	std::string m_nameTileSet;
};





enum Type
{
	GroundType,
	FireType,
	NType = 2
};





struct Stats
{
public:
	Stats() : m_life(0.0f), m_attack(0.0f), m_def(0.0f) {}
	Stats(float life, float attack, float def);

	float getLife() const { return m_life; }
	void setLife(float life) { m_life = life; }
	float getAttack() const { return m_attack; }
	float getDef() const { return m_def; }

private:
	float m_life;

	float m_attack;
	float m_def;

	//For Next
	std::array<float, Type::NType> attack;
	std::array<float, Type::NType> def;
};





struct BattleEntity : public GameObject
{
public:
	BattleEntity() : GameObject() {}
	BattleEntity(const AABBbox& aabbBox, const Stats& stats);

	virtual void update(float deltaTime) override;
	virtual void draw(const GraphicTileSetHandler& gTileSetHandler) override;
	virtual void move(float deltaTime);
	virtual void takeDamage(const std::array<float, Type::NType>& rawDamage);
	virtual void takeDamage(float rawDamage);
	virtual void resetStats();

public:
	AABBbox m_box;
	Stats m_currentStats;
	Stats m_maxStats;

private:

};





struct StaticRectangleWall : public BattleEntity
{
public:
	StaticRectangleWall() :BattleEntity() {}
	StaticRectangleWall(const AABBbox& box, const Stats& stats);
	
	virtual void update(float deltaTime) override;
	virtual void takeDamage(float rawDamage) override;

private:

};





struct RectangleParticle : public BattleEntity
{
public:
	RectangleParticle() :BattleEntity() {}
	RectangleParticle(const AABBbox& box, const Stats& stats);

	virtual void update(float deltaTime) override;
	virtual void draw(const GraphicTileSetHandler& gTileSetHandler) override;
	virtual void move(float deltaTime) override;

public:

private:

};





struct RectangleEntity : public BattleEntity
{
public:
	RectangleEntity() :BattleEntity() {}

	//virtual void update(float deltaTime) override;
	//virtual void draw(const GraphicTileSetHandler& gTileSetHandler) override;

private:
};





struct RectangleHitbox : public BattleEntity
{
public:
	RectangleHitbox() : BattleEntity() {}

	//virtual void update(float deltaTime) override;
	//virtual void draw(const GraphicTileSetHandler& gTileSetHandler) override;

private:
};