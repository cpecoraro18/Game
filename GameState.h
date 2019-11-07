#pragma once
#ifndef SRC_GAMESTATE_H_
#define SRC_GAMESTATE_H_

#include "Entity.h"
#include "Map.h"
#include "State.h"
#include "Game.h"
#include <vector>

class GameState : public State {
public:

	GameState(GameDataRef data);

	~GameState() {}

	bool Init();

	void HandleInput();

	void Update(float dt);

	void Draw();

	void clean();



private:
	GameDataRef data;
	std::vector<class Entity*> characters;
	Entity* player;
	Map* map;
	const int FPS = 60;
	const int frameDelay = 1000/FPS;
	Uint32 frameStart;
	int frameTime;

};
#endif /* SRC_GAMESTATE_H_ */
