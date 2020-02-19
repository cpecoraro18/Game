#include "MovingBlock.h"

MovingBlock::MovingBlock(GameDataRef data, float x, float y, float x2, float y2, float speed, float h, float w) : Block(data, x, y, h, w) {
	startingX = x;
	startingY = y;
	endingX = x2;
	endingY = y2;


}
MovingBlock::MovingBlock(GameDataRef data, float x, float y, float x2, float y2, float speed, float h, float w, int nFrames, int frameSpeed) : Block(data, x, y, h, w, nFrames, frameSpeed) {
	startingX = x;
	startingY = y;
	endingX = x2;
	endingY = y2;

}

void MovingBlock::Update() {


}