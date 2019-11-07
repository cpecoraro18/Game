#pragma once
#ifndef SRC_BLOCK_H_
#define SRC_BLOCK_H_
#include "SDL.h"
#include "Entity.h"
#include "Player.h"
#include "Game.h"

class Block : public Entity {
public:

	Block(GameDataRef data, float x, float y, float h, float w);
	Block(GameDataRef data, float x, float y, float h, float w, int nFrames, int frameSpeed);
	~Block() {}

	void loadtexture(const char* path, int tilex, int tiley);
	void loadHitboxTexture(const char* path, int tilex, int tiley);
	void update(std::vector<class Entity*> collidables, float dt);
	void handleinput(SDL_Event event);
	void draw();
	void handleCollision(Player* player, int onx);

private:
	SDL_Rect src, dest;
	SDL_Texture* texture;
	GameDataRef data;
};

#endif /* SRC_BLOCK_H_ */