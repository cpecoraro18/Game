#pragma once
#ifndef SRC_BLOCK_H_
#define SRC_BLOCK_H_
#include "SDL.h"
#include "Entity.h"
#include "Player.h"

class Block : public Entity {
public:

	Block(GameDataRef data, float x, float y, float h, float w);
	Block(GameDataRef data, float x, float y, float h, float w, int nFrames, int frameSpeed);
	~Block();

	void update(World* world) override;
	void handleinput(SDL_Event event, const Uint8 *keystate);
	void draw();
	void handleCollisions(Player* player, int onx);

private:
};

#endif /* SRC_BLOCK_H_ */