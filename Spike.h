#pragma once
#ifndef SRC_SPIKE_H_
#define SRC_SPIKE_H_
#include "SDL.h"
#include "Entity.h"



class Spike : public Entity {
public:

	Spike(GameDataRef data, float x, float y, float h, float w, bool flipped);

	~Spike();

	void update(std::vector<class Entity*>& collidables, float dt) override;
	void handleinput(SDL_Event event, const Uint8 *keystate);
	void handleCollisions();
	void draw();

private:
	bool flipped;
};

#endif /*SRC_SPIKE_H_ */