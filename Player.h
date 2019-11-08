#pragma once
#ifndef SRC_PLAYERH_H_
#define SRC_PLAYERH_H_

#include "Entity.h"
#include "Game.h"




class Player : public Entity {
public:

	Player(float x, float y, int h, int w, int nFrames, int frameSpeed, GameDataRef data);

	Player(float x, float y, int h, int w, GameDataRef data);

	~Player() {}

	void update(std::vector<class Entity*> collidables, float dt);

	void loadtexture(const char* path, const char* name, int tilex, int tiley);

	void loadtexture(const char* name, int tilex, int tiley);
	
	void loadHitboxTexture(const char* name, int tilex, int tiley);

	void draw();

	void handleinput(SDL_Event event);

	void handleCollisions(std::vector<class Entity*> &collidables, int onx);

	void animate();

	void goRight();

	void goLeft();

	void jump();

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

	GameDataRef data;
	int count;
	int coinCount;
	int keyCount;

	int jumpCount;
	int jumpSpriteCounter;

	bool groundFriction;

	bool airFriction;


};

#endif /* SRC_PLAYERH_H_ */