#pragma once
#ifndef SRC_GAMESTATE_H_
#define SRC_GAMESTATE_H_

#include "Entity.h"
#include "Player.h"
#include "Knight.h"
#include "Bird.h"
#include "Map.h"
#include "Button.h"
#include "State.h"
#include "Game.h"
#include "DEFINITIONS.h"
#include "SDL_mixer.h"
#include <vector>


class GameState : public State {
public:

	GameState(GameDataRef data, const char* Level);
	//free assets!!
	~GameState();

	bool Init();

	void HandleInput();

	void Update(float dt);

	void Draw();

	void HandleClick(int x, int y);

	void clean();



private:
	GameDataRef data;
	std::vector<class Entity*> enemies;
	Player* player;
	Entity* bird;
	Knight* knight;
	Map* map;
	Button* pauseButton;
	const int FPS = 60;
	const int frameDelay = 1000/FPS;
	Uint32 frameStart;
	const Uint8 * keystate;
	int frameTime;

};
#endif /* SRC_GAMESTATE_H_ */
