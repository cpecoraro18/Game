#include "Block.h"
#include "TextureManager.h"
#include <iostream>

Block::Block(GameDataRef data, float x, float y, float h, float w): data(data) {
	type_ = kBlock;
	dead = false;
	this->position = new Vector(x, y);
	this->velocity = new Vector();
	this->acceleration = new Vector();
	this->height = h;
	this->width = w;
	hitbox = new AABB(x, y, w, h);
	src.x = src.y = 0;
	dest.x = x - data->camera.x;
	dest.y = y - data->camera.x;
	dest.h = dest.w = 55;
	src.h = 32;
	src.w = 32;
}

Block::Block(GameDataRef data, float x, float y, float h, float w, int nFrames, int frameSpeed) : data(data) {
	type_ = kBlock;
	dead = false;
	this->position = new Vector(x, y);
	this->velocity = new Vector();
	this->acceleration = new Vector();
	this->height = h;
	this->width = w;
	hitbox = new AABB(x, y, w, h);
	src.x = src.y = 0;
	dest.x = x - data->camera.x;
	dest.y = y - data->camera.x;
	dest.h = dest.w = 45;
	src.h = 32;
	src.w = 32;

	animated = true;
	frames = nFrames;
	speed = frameSpeed;
}

void Block::loadtexture(const char* path, const char* name, int tilex, int tiley) {
	data->texmanager.LoadTexture(path, name, data->renderer);
	this->texture = data->texmanager.GetTexture(name);
	src.x = tilex;
	src.y = tiley;
}
void Block::loadtexture(const char* name, int tilex, int tiley) {
	this->texture = data->texmanager.GetTexture(name);
	src.x = tilex;
	src.y = tiley;
}

void Block::loadHitboxTexture(const char* name, int tilex, int tiley) {
	this->hitboxTexture = data->texmanager.GetTexture(name);
}


void Block::draw() {
	dest.x = position->x - data->camera.x;
	dest.y = position->y - data->camera.y;
	data->texmanager.Draw(texture, src, dest, data->renderer);
}

void Block::update(std::vector<class Entity*> collidables, float dt) {
	hitbox->setDimentions(position->x, position->y);
	if (animated) {
		src.x = src.w*static_cast<int>((SDL_GetTicks() / speed) % frames);
	}
	return;
}
void Block::handleinput(SDL_Event event) {
	return;
}

void Block::handleCollision(Player* player, int onx) {
	

}