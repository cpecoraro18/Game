#pragma once
#ifndef SRC_ARROW_H_
#define SRC_ARROW_H_
#include "Game.h"
#include "Vector.h"
#include "Entity.h"
#include "Enemy.h"
#include "AABB.h"
#include "World.h"
#include <vector>


class Arrow{
public:

	Arrow(GameDataRef data, float x, float y, float h, float w, float speedx, float speedy);
	~Arrow();

	void loadtexture(const char* name, int tilex, int tiley);
	void loadHitboxTexture(const char* name, int tilex, int tiley);

	void update(World* world);
	void handleCollisions(std::vector<class Entity*>& collidables);
	void handleinput(SDL_Event event);
	void draw();
	int getNumCoinsHit();
	int getNumKeysHit();


	bool dead;
	bool stuck;

private:
	int width;
	int height;
	double angle;
	Vector* position;
	Vector* velocity;
	AABB* hitbox;

	int numCoinsHit;
	int numKeysHit;
	
	int frames;
	int speed;
	int count;
	
	bool animated;
	SDL_Rect src, dest;
	SDL_Texture* texture;
	GameDataRef data;

	SDL_Texture* hitboxTexture;
	SDL_Rect srcHitbox, destHitbox;
	int hitboxXBuffer;
	int hitboxYBuffer;
	int hitboxWidthBuffer;
	int hitboxHeightBuffer;
};

#endif /* SRC_ARROW_H_ */