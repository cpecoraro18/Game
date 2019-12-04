#pragma once
#ifndef SRC_MOVINGBLOCK_H_
#define SRC_MOVINGBLOCK_H_
#include "SDL.h"
#include "Block.h"
#include "Player.h"

class MovingBlock : public Block {
public:

	MovingBlock(GameDataRef data, float x, float y, float x2, float y2, float speed, float h, float w);
	MovingBlock(GameDataRef data, float x, float y, float x2, float y2, float speed, float h, float w, int nFrames, int frameSpeed);
	~MovingBlock() {}

	void Update();

private:
	float startingX;
	float startingY;
	float endingX;
	float endingY;

};

#endif /* SRC_MOVINGBLOCK_H_ */
