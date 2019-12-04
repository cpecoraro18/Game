#pragma once
#ifndef SRC_MAP_H_
#define SRC_MAP_H_

#include "SDL.h"
#include "SDL_image.h"
#include "Block.h"
#include "Entity.h"
#include "Game.h"
#include <vector>
#include <string>

class Map {
public:

	Map() {}
	Map(GameDataRef data);

	~Map();

	void LoadCollidables(std::string path);

	void LoadBackground(std::string path, std::string level);

	void LoadCoins(std::string path);

	void UpdateMap(float dt);

	void DrawMap();
	
	std::vector<class Entity*> getCollidables() { return collidables; }

private:
	SDL_Rect src, dest;
	SDL_Texture* background;
	std::vector<class Entity*> collidables;
	int mapWidth;
	int mapHeight;

	GameDataRef data;



};

#endif /* SRC_MAP_H_ */