#pragma once

#include "General/Options.h"

#include "Input/Input.h"

#include "Graphic/Image.h"

#include "World/World.h"
#include "World/Level.h"

#include "StatusHandler.h"

#include "Camera/Camera.h"

#include "Time/Delay.h"





class Game
{
public:
	struct GamePhase
	{
		enum Phase
		{
			NonePhase = -1,
			Exploring,
			Battle,
			Dialoging
		};

		enum StatusGamePhase
		{
			NoneStatusGamePhase=-1,
			On,
			Pause,
			Off
		};

	public:
		GamePhase() :status(StatusGamePhase::Off){}
		GamePhase(Phase phase): phase(phase) {}

		bool operator==(GamePhase other)
		{
			return phase == other.phase;
		}

		StatusGamePhase status;
		Phase phase;
	};

	static Game& get()
	{
		static Game game;
		return game;
	}

	void runLoop();

	void init();
	void shutdown();

protected:
	Game() {}

	//Principle Method
	void processInput();
	void update();
	void generateOutput();
	//Principle Method

	//Secondary Method
	void clearColorScreen(const Color& clearColor);
	void renderGraphics();
	void updateDeltaTime();
	void sleep();
	void first();
	//Secondary Method

protected:
	bool m_isRunning;

	bool m_isFirst;

	double s_deltaTime;
	uint32_t s_ticksCount;

	Vector2i screenDimension;
	Level currentLevel;

	StatusHandler<GamePhase> statusHandler;

	TileSetHandler entityTileSetHandler;

	int currentEnemy = -1;
protected:

	Entity entity;
};

//Rinominare tutti i getInstance() dei singleton come get()

//Regole:
//Lasciare sempre tre spazi tra le funzioni di una classe
//Lasciare sempre cinque tra una classe e l'altra sia in .h che in .cpp