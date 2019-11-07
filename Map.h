#pragma once
#ifndef SRC_MAP_H_
#define SRC_MAP_H_

#include "SDL.h"
#include "SDL_image.h"
#include "Block.h"
#include "Entity.h"
#include "Game.h"
#include <vector>

class Map {
public:

	Map() {}
	Map(GameDataRef data);
	~Map() {}

	void LoadCollidables(char* path);

	void LoadBackground(char* path);

	void LoadCoins(char* path);

	void UpdateMap(float dt);

	void DrawMap(GameDataRef data);
	
	std::vector<class Entity*> getCollidables() { return collidables; }

private:
	SDL_Rect src, dest;
	std::vector<class Block*> blocks;
	std::vector<class Entity*> collidables;
	int mapWidth;
	int mapHeight;

	GameDataRef data;



};

#endif /* SRC_GAME_H_ */