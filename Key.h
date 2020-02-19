#pragma once
#ifndef SRC_KEY_H_
#define SRC_KEY_H_
#include "SDL.h"
#include "Entity.h"


class Key : public Entity {
public:

	Key(GameDataRef data, float x, float y, float h, float w, int nFrames, int frameSpeed);
	~Key();
	void update(World* world) override;
	void handleinput(SDL_Event event, const Uint8 *keystate);
	void handleCollisions();
	void draw();

private:
};

#endif /*SRC_KEY_H_ */