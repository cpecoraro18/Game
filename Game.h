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


	void handleEvents(SDL_Event event);

	void update();

	//void render();

	void clean();


private:
	Window* window;
	static SDL_Event event;
	bool running;

	std::vector<class Entity*> entities;
	Entity* player;
	Map* map;
	const int FPS = 60;
	const int frameDelay = 1000/FPS;
	Uint32 frameStart;
	int frameTime;

};
#endif /* SRC_GAME_H_ */
