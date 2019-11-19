#pragma once
#ifndef SRC_PLAYER_H_
#define SRC_PLAYER_H_

#include "Entity.h"
#include "Bow.h"
#include "Arrow.h"
#include "SDL_mixer.h"
#include <vector>
#include "CoinCounter.h"




class Player : public Entity {
public:

	Player(int x, int y, int h, int w, int nFrames, int frameSpeed, GameDataRef data);

	~Player() {}

	void update(std::vector<class Entity*> collidables, std::vector<class Entity*> enemies, float dt);

	void draw();

	void handleinput(SDL_Event event, const Uint8 *keystate);

	void handleCollisions(std::vector<class Entity*> &collidables, int onx, float dt);

	void Animate();

	void goRight();

	void goLeft();

	void jump();

	void die();

	void shoot(float speedx, float speedy);

	void aim();

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

	

	int count;
	int coinCount;
	int keyCount;

	int jumpCount;
	int jumpSpriteCounter;

	bool groundFriction;
	bool airFriction;

	bool shooting;
	bool shootingLeft;
	bool shootingRight;
	double angle;
	std::vector<class Arrow*> arrows;

	int mouseX, mouseY;
	SDL_Rect srcarm, destarm;
	SDL_Texture* armtexture;

	Mix_Chunk* jumpSound;
	Mix_Chunk* coinSound;
	Mix_Chunk* bowSound;

	CoinCounter* coinCounter;


};

#endif /* SRC_PLAYER_H_ */