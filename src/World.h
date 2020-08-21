#pragma once
#ifndef SRC_WORLD_H_
#define SRC_WORLD_H_

#include "SDL.h"
#include "SDL_image.h"
#include "Block.h"
#include "Game.h"
#include "Entity.h"
#include <vector>
#include <string>


class World {
public:

	World() {}
	World(GameDataRef data);

	~World();

	void LoadCollidables(std::string path);

	void LoadBackground(std::string background);

	void LoadCoins(std::string path);

	void LoadCharacters(std::string path);

	void UpdateWorld();

	void DrawWorld();



	std::vector<class Entity*> collidables;
	std::vector<class Entity*> enemies;
	Player* player;

	int worldWidth;
	int worldHeight;

private:
	SDL_Rect src, dest;
	SDL_Texture* background;
	
	

	GameDataRef data;



};

#endif /* SRC_WORLD_H_ */