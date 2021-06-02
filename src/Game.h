#pragma once

#include "Graphic/Image.h"

#include "World/Level.h"

#include "TileSet.h"





class Game
{
public:
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
	//Secondary Method

protected:
	bool m_isRunning;

	bool m_isFirst;

	Vector2i screenDimension;


protected:

	Level level;

	Vector2f pos;

};

//Rinominare tutti i getInstance() dei singleton come get()

//Regole:
//Lasciare sempre tre spazi tra le funzioni di una classe
//Lasciare sempre cinque tra una classe e l'altra sia in .h che in .cpp