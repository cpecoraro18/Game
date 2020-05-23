#include "Spike.h"
#include "TextureManager.h"

Spike::Spike(GameDataRef data, float x, float y, float h, float w, bool flipped) :Entity(x, y, h, w, 1, 0, data) {
	type_ = kSpike;
	dead = false;
	this->flipped = flipped;

	src.x = 0;
	src.y = 0;
	src.h = 32;
	src.w = 32;
	if (flipped) {
		hitbox = new AABB(x+20, y, w-20, h - 850);
		destHitbox.x = position->x + 20 - data->camera.x;
		destHitbox.y = position->y - data->camera.y;
		destHitbox.h = height - 85;
		destHitbox.w = width - 20;
	}
	else {
		hitbox = new AABB(x + 20, y + 85, w - 200, h);
		destHitbox.x = position->x + 20 - data->camera.x;
		destHitbox.y = position->y + 85 - data->camera.y;
		destHitbox.h = height;
		destHitbox.w = width - 20;
	}
}


Spike::~Spike() { 
	//printf("Deleting Spike\n"); 
	delete hitbox;
}
void Spike::update(World* world) {
	hitbox->setDimentions(position->x+20, position->y+40);
}

void Spike::handleCollisions() {
	src.y = 32;
	dead = true;

}
void Spike::handleinput(SDL_Event event, const Uint8 *keystate) {
	return;

}
void Spike::draw() {

	dest.x = position->x - data->camera.x;
	dest.y = position->y - data->camera.y;
	if (flipped) {
		destHitbox.x = position->x + 10 - data->camera.x;
		destHitbox.y = position->y - data->camera.y;
	}
	else {
		destHitbox.x = position->x + 10 - data->camera.x;
		destHitbox.y = position->y + 60 - data->camera.y;
	}
	data->texmanager.Draw(texture, src, dest, data->renderer);
	//data->texmanager.Draw(hitboxTexture, srcHitbox, destHitbox, data->renderer);

}