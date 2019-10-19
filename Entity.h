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

	virtual void update(std::vector<class Entity*> &entities) = 0;
	virtual void draw() = 0;
	virtual void handleinput(SDL_Event event) = 0;
	virtual void loadtexture(const char* path) = 0;


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
	SDL_Texture* texture;
	bool isAlive;
	AABB* hitbox;

private:

	EntityType type_;

};

#endif /* SRC_ENTITY_H_ */