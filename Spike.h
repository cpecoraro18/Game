#pragma once
#ifndef SRC_SPIKE_H_
#define SRC_SPIKE_H_
#include "SDL.h"
#include "Entity.h"
#include "Game.h"


class Spike : public Entity {
public:

	Spike(GameDataRef data, float x, float y, float h, float w, bool flipped);
	~Spike() {}

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