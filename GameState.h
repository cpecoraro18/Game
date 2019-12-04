#pragma once
#ifndef SRC_GAMESTATE_H_
#define SRC_GAMESTATE_H_

#include "Enemy.h"
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
#include <string>
#include <fstream>


class GameState : public State {
public:

	GameState(GameDataRef data, std::string level);

	~GameState();

	void Identify() { printf("Game State"); }

	bool Init();
	void HandleInput();
	void Update(float dt);
	void Draw();
	void HandleClick(int x, int y);

	void loadCharacters(std::string path);
	void Resume();
	void clean();

	bool playing;

private:
	GameDataRef data;
	std::vector<class Enemy*> enemies;
	Player* player;
	Entity* bird;
	Knight* knight;
	Map* map;
	Button* pauseButton;
	int levelWidth;
	int levelHeight;

	std::string level;

	bool paused;

	const Uint8 * keystate;

	Mix_Music* backgroundMusic;

};
#endif /* SRC_GAMESTATE_H_ */
