#pragma once
#ifndef SRC_ENEMY_H_
#define SRC_ENEMY_H_

#include "Entity.h"


class Player;
class Enemy : public Entity {
public:

	Enemy(int x, int y, int h, int w, int nFrames, int frameSpeed, GameDataRef data) : Entity(x, y, h, w, nFrames, frameSpeed, data) {}
	Enemy() {}
	~Enemy() {}

	virtual void update(std::vector<class Entity*>& collidables, float dt, Player* player) {}
	void draw() {}
	void handleCollisions() {}
	void Animate() {}

	Vector getPosition() { return *position; }

	
private:
};
#endif /*SRC_ENEMY_H_ */