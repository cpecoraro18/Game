#include "Bow.h"

#include <iostream>

Bow::Bow(GameDataRef data, float x, float y, float h, float w) : data(data) {
	this->position = new Vector(x + 10, y);
	this->height = h;
	this->width = w;
	src.x = src.y = 0;
	dest.x = x - data->camera.x;
	dest.y = y - data->camera.x;
	dest.h = h;
	dest.w = w;
	src.h = 32;
	src.w = 32;
	frames = 1;
	speed = 100;

	loadtexture("Images/Bow.png", "bow", 0, 0);
}


void Bow::loadtexture(const char* path, const char* name, int tilex, int tiley) {
	data->texmanager.LoadTexture(path, name, data->renderer);
	this->texture = data->texmanager.GetTexture(name);
	src.x = tilex;
	src.y = tiley;
}
void Bow::loadtexture(const char* name, int tilex, int tiley) {
	this->texture = data->texmanager.GetTexture(name);
	src.x = tilex;
	src.y = tiley;
}


void Bow::draw() {
	dest.x = position->x - data->camera.x;
	dest.y = position->y - data->camera.y;
	data->texmanager.Draw(texture, src, dest, data->renderer);
}

void Bow::update( float dt, int x, int y) {
	position->x = x + 30;
	position->y = y+15;
	//src.x = src.w*static_cast<int>((SDL_GetTicks() / speed) % frames);
	return;
}
void Bow::handleinput(SDL_Event event) {
	return;
}

