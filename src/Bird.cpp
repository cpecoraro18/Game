#include "Bird.h"

Bird::Bird(int x, int y, int h, int w, int nFrames, int frameSpeed, GameDataRef data) : Enemy(x, y, h, w, nFrames, frameSpeed, data) {
	type_ = kBird;
	dead = false;
	hitbox = new AABB(x, y, w, h);
	destHitbox.x = x - data->camera.x;
	destHitbox.y = y - data->camera.y;
	destHitbox.w = w;
	destHitbox.h = h;

	src.x = 0;
	src.y = 0;
	src.w = 32;
	src.h = 32;


	texture = data->texmanager.GetTexture("bird");
	hitboxTexture = data->texmanager.GetTexture("hitbox");

	frames = nFrames;
	speed = frameSpeed;
	goLeft();
}

Bird::~Bird() { 
	//printf("Deleting Bird\n"); 
	delete hitbox;
}

void Bird::update(World* world) {
	Entity::update(world);
	if (position->x < 0 || position->x + width > world->worldWidth) {
		acceleration->x *= -1;
		velocity->x *= -1;
	}
	position->x += velocity->x;
	hitbox->setDimentions(position->x, position->y);
	if (animated) {
		Animate();
	}
	return;
}

void Bird::draw() {
	if (dead) {
		return;
	}
	dest.x = position->x - data->camera.x;
	dest.y = position->y - data->camera.y;
	destHitbox.x = position->x - data->camera.x;
	destHitbox.y = position->y - data->camera.y;

	data->texmanager.Draw(texture, src, dest, data->renderer);
	//data->texmanager.Draw(hitboxTexture, srcHitbox, destHitbox, data->renderer);
}

void Bird::handleCollisions() {
	die();
}

void Bird::Animate() {
	if (velocity->x > 0) {
		src.y = 1*32;
	}
	else {
		src.y = 0;
	}
	Entity::Animate();
	
}

void Bird::goLeft() {
	velocity->x = -3.0f;
}
void Bird::goRight() {
	velocity->x = 3.0f;
}



void Bird::die() {
	acceleration->y = 5;
}