#include <SDL.h>
#undef main
#include <stdio.h>
#include "Game.h"


int main(int argc, char** argv)
{
	Game* game = new Game();
	bool closeApp = false;

	if (game->init()) {
		game->run();
	}

	return 0;



}