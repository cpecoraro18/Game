#pragma once
#ifndef SRC_ENTITY_H_
#define SRC_ENTITY_H_

#include <vector>
#include "SDL.h"
#include "Entity_type.h"
#include "Game.h"
#include "Vector.h"
#include "AABB.h"
#include "Collision.h"

class World;

class Entity {
public:

	Entity(int x, int y, int h, int w, int nFrames, int frameSpeed, GameDataRef data);
	Entity() {}

	virtual ~Entity();

	virtual void update(World* world);
	virtual void draw() = 0;
	virtual void handleinput(SDL_Event event, const Uint8* keystate) {}
	virtual void Animate();
	virtual void handleCollisions() {};

	void loadtexture(const char* name, int tilex, int tiley);
	void loadHitboxTexture(const char* name, int tilex, int tiley);


	EntityType get_type() const { return type_; }
	void set_type(EntityType et) { type_ = et; }

	//size
	int width;
	int height;
	//movement
	Vector* position;
	Vector* oldPosition;
	Vector* velocity;
	Vector* oldVelocity;
	Vector* acceleration;
	//rendering
	SDL_Rect src, dest;
	SDL_Rect srcHitbox, destHitbox;
	SDL_Texture* texture;
	SDL_Texture* hitboxTexture;

	bool animated = false;
	int frames = 0;
	int speed = 100;

	//hitbox
	int hitboxXBuffer;
	int hitboxYBuffer;
	int hitboxWidthBuffer;
	int hitboxHeightBuffer;
	AABB* hitbox;
	//entity info
	EntityType type_;
	bool dead;
	GameDataRef data;

private:

};

#endif /* SRC_ENTITY_H_ */