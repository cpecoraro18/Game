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



class Entity {
public:

	Entity(int x, int y, int h, int w, int nFrames, int frameSpeed, GameDataRef data);
	Entity() {}

	~Entity() = default;

	virtual void update(std::vector<class Entity*> collidables, float dt);
	virtual void draw() = 0;
	virtual void handleinput(SDL_Event event, const Uint8* keystate) {}
	void loadtexture(const char* path, const char* name, int tilex, int tiley);
	void loadtexture(const char * name, int tilex, int tiley);
	void loadHitboxTexture(const char* path, int tilex, int tiley);
	virtual void Animate();
	virtual void handleCollisions() {};


	EntityType get_type() const { return type_; }
	void set_type(EntityType et) { type_ = et; }


	int width;
	int height;

	Vector* position;
	Vector* oldPosition;
	Vector* velocity;
	Vector* oldVelocity;
	Vector* acceleration;

	SDL_Rect src, dest;
	SDL_Rect srcHitbox, destHitbox;
	SDL_Texture* texture;
	SDL_Texture* hitboxTexture;

	int hitboxXBuffer;
	int hitboxYBuffer;
	int hitboxWidthBuffer;
	int hitboxHeightBuffer;

	AABB* hitbox;

	bool animated = false;
	int frames = 0;
	int speed = 100;

	EntityType type_;
	bool dead;
	GameDataRef data;

private:

};

#endif /* SRC_ENTITY_H_ */