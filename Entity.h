#pragma once
#ifndef SRC_ENTITY_H_
#define SRC_ENTITY_H_

#include <vector>
#include "SDL.h"
#include "Entity_type.h"
#include "Vector.h"
#include "AABB.h"
#include "Collision.h"



class Entity {
public:

	Entity() {}

	~Entity() = default;

	virtual void update(std::vector<class Entity*> collidables, float dt) = 0;
	virtual void draw() = 0;
	virtual void handleinput(SDL_Event event) = 0;
	virtual void loadtexture(const char* path, int tilex, int tiley) = 0;
	virtual void loadHitboxTexture(const char* path, int tilex, int tiley) = 0;
	virtual void handleCollision() {};


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
	bool isAlive;
	AABB* hitbox;
	bool animated = false;
	int frames = 0;
	int speed = 100;
	EntityType type_;
	bool dead;
private:

	
	

};

#endif /* SRC_ENTITY_H_ */