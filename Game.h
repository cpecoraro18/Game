#pragma once
#ifndef SRC_GAME_H_
#define SRC_GAME_H_


#include "Window.h"
#include "Entity.h"
#include "Map.h"
#include <vector>

class Game {
public:

	Game() {}

	~Game() {}

	bool init();

	void run();


	void handleEvents();

	void update();

	//void render();

	void clean();


private:
	Window* window;

	bool running;
	std::vector<class Entity*> entities;
	Entity* player;
	Map* map;
	const int frameDelay{ 60 };
	const int dt{ 1000 / frameDelay};
	Uint32 frameStart;
	int frameTime;

};
#endif /* SRC_GAME_H_ */
