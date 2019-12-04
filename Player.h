#pragma once
#ifndef SRC_PLAYER_H_
#define SRC_PLAYER_H_

#include "Entity.h"
#include "Bow.h"
#include "Arrow.h"
#include "SDL_mixer.h"
#include <vector>
#include "CoinCounter.h"
#include "State.h"

class Player : public Entity {
public:

	Player(int x, int y, int h, int w, int nFrames, int frameSpeed, GameDataRef data);

	~Player();

	void update(std::vector<class Entity*>& collidables, float dt);

	void draw();

	void handleinput(SDL_Event event, const Uint8 *keystate);

	void handleCollisions(std::vector<class Entity*>& collidables, int onx, float dt);

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

	Vector* spawnPoint;

private:

	

	int count;
	int deathCount;
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
	std::vector<std::unique_ptr<class Arrow>> arrows;

	int mouseX, mouseY;

	SDL_Rect srcarm, destarm;
	SDL_Texture* armtexture;

	Mix_Chunk* jumpSound;
	Mix_Chunk* bowSound;

	CoinCounter* coinCounter;

	float jumpVelocity = -20.0f;
	float moveSpeed = 2.0f;
	float shootSpeed = 40.0f;

	bool playing = true;

};

#endif /* SRC_PLAYER_H_ */