#include "Coin.h"
#include "TextureManager.h"

Coin::Coin(GameDataRef data, float x, float y, float h, float w, int nFrames, int frameSpeed) : data(data) {
	type_ = kCoin;
	dead = false;
	this->position = new Vector(x+5, y+5);
	this->velocity = new Vector();
	this->acceleration = new Vector();
	this->height = h;
	this->width = w;
	hitbox = new AABB(x+5, y+5, w, h);
	src.x = src.y = 0;
	dest.x = x - data->camera.x;
	dest.y = y - data->camera.x;
	dest.h = dest.w = h;
	src.h = 32;
	src.w = 32;

	animated = true;
	frames = nFrames;
	speed = frameSpeed;

}


void Coin::loadtexture(const char* path, int tilex, int tiley) {
	this->texture = TextureManager::LoadTexture(path, data);
	src.x = tilex;
	src.y = tiley;

}

void Coin::loadHitboxTexture(const char* path, int tilex, int tiley) {
	this->hitboxTexture = TextureManager::LoadTexture(path, data);
}

void Coin::update(std::vector<class Entity*> collidables, float dt) {
	hitbox->setDimentions(position->x, position->y);
	src.x = src.w*static_cast<int>((SDL_GetTicks() / speed) % frames);
}

void Coin::handleCollision() {
	src.y = 32;
	dead = true;

}
void Coin::handleinput(SDL_Event event) {
	return;

}
void Coin::draw() {
	dest.x = position->x + 5 - data->camera.x;
	dest.y = position->y + 5- data->camera.y;
	TextureManager::Draw(texture, src, dest, data);

}