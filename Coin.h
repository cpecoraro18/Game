#pragma once
#ifndef SRC_COIN_H_
#define SRC_COIN_H_
#include "SDL.h"
#include "SDL_mixer.h"
#include "Entity.h"


class Coin : public Entity {
public:

	Coin(GameDataRef data, float x, float y, float h, float w, int nFrames, int frameSpeed);
	~Coin();

	void update(std::vector<class Entity*>& collidables, float dt) override;
	void handleinput(SDL_Event event, const Uint8 *keystate);
	void handleCollisions();
	void draw();

private:
	Mix_Chunk* coinSound;
};

#endif /*SRC_COIN_H_ */