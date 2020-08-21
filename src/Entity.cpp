#include "Entity.h"
#include "World.h"
Vector* gravity = new Vector(0, 1);



Entity::Entity(int x, int y, int h, int w, int nFrames, int frameSpeed, GameDataRef data) : data(data), height(h), width(w), frames(nFrames), speed(frameSpeed) {
	//set physics
	this->position = new Vector(x, y);
	this->velocity = new Vector();
	this->acceleration = new Vector();
	//hitbox sprite source
	hitboxTexture = data->texmanager.GetTexture("hitbox");
	srcHitbox.x = 0;
	srcHitbox.y = 0;
	srcHitbox.h = 32;
	srcHitbox.w = 32;
	//sprite dest
	dest.x = position->x - data->camera.x;
	dest.y = position->y - data->camera.y;
	dest.h = height;
	dest.w = width;
	//animation
	if (nFrames > 1) {
		animated = true;
		speed = frameSpeed;
	}
	else {
		animated = false;
	}
}


Entity::~Entity() {

	//printf("Destroying Entity\n");

	delete position;
	delete velocity;
	delete acceleration;

}

void Entity::update(World* world) {
	//apply accelerations
	velocity->x += gravity->x;
	velocity->y += gravity->y;
	velocity->x += acceleration->x;
	velocity->y += acceleration->y;



}

void Entity::loadHitboxTexture(const char* name, int tilex, int tiley) {
	hitboxTexture = data->texmanager.GetTexture(name);

}

void Entity::loadtexture(const char* name, int tilex, int tiley) {
	texture = data->texmanager.GetTexture(name);
	src.x = tilex;
	src.y = tiley;
}
void Entity::Animate() {
	src.x = src.w * static_cast<int>((SDL_GetTicks() / speed) % frames);
}