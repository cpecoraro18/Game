#pragma once
#pragma once
#ifndef SRC_KNIGHT_H_
#define SRC_KNIGHT_H_

#include "Vector.h"
#include "Enemy.h"
#include "Player.h"

class Knight : public Enemy {
public:

	Knight(int x, int y, int h, int w, int nFrames, int frameSpeed, GameDataRef data);

	Knight();

	~Knight(); 

	void update(std::vector<class Entity*>& collidables, float dt, Player* player);

	void draw();

	void handleCollisions();

	void handleCollisions(std::vector<class Entity*>& collidables, int onx, float dt);

	void Animate(Player* player);

	void goRight();

	void goLeft();
	
	void attack(Player* player);


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

	bool attacking;


	int health = 50;
private:






};
#endif /*SRC_KNIGHT_H_ */