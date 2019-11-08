#include "Spike.h"
#include "TextureManager.h"

Spike::Spike(GameDataRef data, float x, float y, float h, float w, bool flipped) : data(data) {
	type_ = kSpike;
	dead = false;
	this->position = new Vector(x, y);
	this->velocity = new Vector();
	this->acceleration = new Vector();
	this->height = h;
	this->width = w;
	if (flipped)
		hitbox = new AABB(x + 20, y, w - 20, h-40);
	else
		hitbox = new AABB(x+20, y+40, w-20, h);
	src.x = src.y = 0;
	dest.x = x - data->camera.x;
	dest.y = y - data->camera.x;
	dest.h = dest.w = 55;
	src.h = 32;
	src.w = 32;


}


void Spike::loadtexture(const char* path, const char* name, int tilex, int tiley) {
	data->texmanager.LoadTexture(path, name, data->renderer);
	texture = data->texmanager.GetTexture(name);

}

void Spike::loadtexture(const char* name, int tilex, int tiley) {
	texture = data->texmanager.GetTexture(name);
	src.x = tilex;
	src.y = tiley;

}

void Spike::loadHitboxTexture(const char* name, int tilex, int tiley) {
	this->hitboxTexture = data->texmanager.GetTexture(name);
}
void Spike::update(std::vector<class Entity*> collidables, float dt) {
	hitbox->setDimentions(position->x+20, position->y+40);
}

void Spike::handleCollision() {
	src.y = 32;
	dead = true;

}
void Spike::handleinput(SDL_Event event) {
	return;

}
void Spike::draw() {
	dest.x = position->x - data->camera.x;
	dest.y = position->y - data->camera.y;
	data->texmanager.Draw(texture, src, dest, data->renderer);

}