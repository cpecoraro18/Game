#pragma once
#ifndef SRC_COIN_H_
#define SRC_COIN_H_
#include "SDL.h"
#include "Entity.h"
#include "Game.h"


class Coin : public Entity {
public:

	Coin(GameDataRef data, float x, float y, float h, float w, int nFrames, int frameSpeed);
	~Coin() {}

	void loadtexture(const char* path, int tilex, int tiley);
	void loadHitboxTexture(const char* path, int tilex, int tiley);
	void update(std::vector<class Entity*> collidables, float dt);
	void handleinput(SDL_Event event);
	void handleCollision();
	void draw();

private:
	SDL_Rect src, dest;
	SDL_Texture* texture;
	GameDataRef data;
};

#endif /*SRC_COIN_H_ */