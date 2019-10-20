#include "Block.h"
#include "TextureManager.h"
#include "Window.h"
#include <iostream>

Block::Block(float x, float y, float h, float w) {
	this->position = new Vector(x, y);
	this->velocity = new Vector();
	this->acceleration = new Vector();
	this->height = h;
	this->width = w;
	hitbox = new AABB(x, y, w, h);
	src.x = src.y = 0;
	dest.x = x - Window::camera.x;
	dest.y = y - Window::camera.x;
	dest.h = dest.w = 45;
	src.h = 32;
	src.w = 32;
}


void Block::loadtexture(const char* path) {
	this->texture = TextureManager::LoadTexture(path);
}

void Block::draw() {
	dest.x = position->x - Window::camera.x;
	dest.y = position->y - Window::camera.y;
	TextureManager::Draw(texture, src, dest);
}

void Block::update(std::vector<class Entity*> &entities) {
	hitbox->setDimentions(position->x, position->y);
	return;
}
void Block::handleinput(SDL_Event event) {
	return;
}