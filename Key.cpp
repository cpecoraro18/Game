#include "Key.h"
#include "TextureManager.h"

Key::Key(GameDataRef data, float x, float y, float h, float w, int nFrames, int frameSpeed) : data(data) {
	type_ = kKey;
	dead = false;
	this->position = new Vector(x + 5, y + 5);
	this->velocity = new Vector();
	this->acceleration = new Vector();
	this->height = h;
	this->width = w;
	hitbox = new AABB(x + 5, y + 5, w, h);
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


void Key::loadtexture(const char* path, const char* name, int tilex, int tiley) {
	data->texmanager.LoadTexture(path, name, data->renderer);
	this->texture = data->texmanager.GetTexture(name);
	src.x = tilex;
	src.y = tiley;
}
void Key::loadtexture(const char* name, int tilex, int tiley) {
	this->texture = data->texmanager.GetTexture(name);
	src.x = tilex;
	src.y = tiley;
}

void Key::loadHitboxTexture(const char* name, int tilex, int tiley) {
	this->hitboxTexture = data->texmanager.GetTexture(name);
}

void Key::update(std::vector<class Entity*> collidables, float dt) {
	hitbox->setDimentions(position->x, position->y);
	src.x = src.w*static_cast<int>((SDL_GetTicks() / speed) % frames);
}

void Key::handleCollision() {
	src.y = 32;
	dead = true;

}
void Key::handleinput(SDL_Event event) {
	return;

}
void Key::draw() {
	dest.x = position->x + 5 - data->camera.x;
	dest.y = position->y + 5 - data->camera.y;
	data->texmanager.Draw(texture, src, dest, data->renderer);

}