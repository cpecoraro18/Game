#pragma once
#ifndef SRC_MAP_H_
#define SRC_MAP_H_

#include "SDL.h"
#include "SDL_image.h"
#include "Block.h"
#include "Entity.h"
#include <vector>

class Map {
public:

	Map();
	~Map() {}

	void LoadMap(int arr[20][25], const char* background, std::vector<class Entity*> &entities);

	void DrawMap();

private:
	SDL_Rect src, dest;
	std::vector<class Block*> blocks;
	SDL_Texture* dirt;
	SDL_Texture* grass;
	SDL_Texture* water;
	SDL_Texture* cloud;
	SDL_Texture* background;



};

#endif /* SRC_GAME_H_ */