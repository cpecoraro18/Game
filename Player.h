#pragma once
#ifndef SRC_PLAYERH_H_
#define SRC_PLAYERH_H_

#include "Entity.h"




class Player : public Entity {
public:

	Player(float x, float y, int h, int w);

	~Player() {}

	void update(std::vector<class Entity*> &entities);

	void loadtexture(const char* path);

	void draw();

	void handleinput(SDL_Event event);

	void handleCollisions(std::vector<class Entity*> &entities, int onx);

	void goRight();

	void goLeft();

	void jump();

	Vector getPosition() { return *position; }


private:
	bool mPushedRightWall;
	bool mPushesRightWall;

	bool mPushedLeftWall;
	bool mPushesLeftWall;

	bool mWasOnGround;
	bool mOnGround;

	bool mWasAtCeiling;
	bool mAtCeiling;

	int count;

	int jumpCount;

	bool groundFriction;

	bool airFriction;




};

#endif /* SRC_PLAYERH_H_ */