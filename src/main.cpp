#include "Game.h"
#include "Math/Vector.h"

#include <iostream>





int main()
{
	Game::get().init();

	Game::get().runLoop();

	Game::get().shutdown();

	return 0;
}