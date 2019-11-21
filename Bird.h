#pragma once
#ifndef SRC_BIRD_H_
#define SRC_BIRD_H_

#include "Vector.h"
#include "Entity.h"

class Bird : public Entity {
public:

	Bird(int x, int y, int h, int w, int nFrames, int frameSpeed, GameDataRef data);

	~Bird();

	void update(std::vector<class Entity*> collidables, float dt) override;
	void draw();
	void handleCollisions();
	void Animate();

	void goRight();
	void goLeft();
	void die();

	Vector getPosition() { return *position; }

	bool mPushedRightWall;
	bool mPushesRightWall;

	bool mPushedLeftWall;
	bool mPushesLeftWall;

	bool mWasOnGround;
	bool mOnGround;

	bool mWasAtCeiling;
	bool mAtCeiling;

private:
};
#endif /*SRC_BIRD_H_ */