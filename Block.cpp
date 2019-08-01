#include "Block.h"
#include <iostream>

Block::Block(float x, float y, float h, float w) {
	this->position = new Vector(x, y);
	this->velocity = new Vector();
	this->acceleration = new Vector();
	this->height = h;
	this->width = w;
	hitbox = new AABB(x, y, w, h);
	src.x = src.y = 0;
	dest.x = x;
	dest.y = y;
	dest.h = dest.w = 32;
	src.h = 32;
	src.w = 32;
}


void Block::loadtexture(const char* path, SDL_Renderer* ren) {
	this->texture = TextureManager::LoadTexture(path, ren);
}

void Block::draw(SDL_Renderer* ren) {
	dest.x = position->x;
	dest.y = position->y;
	TextureManager::Draw(texture, ren, src, dest);
}

void Block::update(std::vector<class Entity*> &entities) {
	hitbox->setDimentions(position->x, position->y);
	return;
}
void Block::handleinput(SDL_Event event) {
	return;
}
