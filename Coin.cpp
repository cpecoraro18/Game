#include "Coin.h"
#include "TextureManager.h"

Coin::Coin(GameDataRef data, float x, float y, float h, float w, int nFrames, int frameSpeed) : Entity(x, y, h, w, nFrames, frameSpeed, data) {
	type_ = kCoin;
	coinSound = data->audioManager.GetChunk("coinSound");
	dead = false;
	hitbox = new AABB(x+5, y+5, w, h);

	src.x = 0;
	src.y = 0;
	src.h = 32;
	src.w = 32;
}

Coin::~Coin() {
//	printf("Deleting Coin\n");
	delete hitbox;
}


void Coin::update(std::vector<class Entity*> collidables, float dt) {
	Entity::update(collidables, dt);
	hitbox->setDimentions(position->x, position->y);
	Entity::Animate();
}

void Coin::handleCollisions() {
	Mix_PlayChannel(-1, coinSound, 0);
	src.y = 32;
	dead = true;

}
void Coin::handleinput(SDL_Event event, const Uint8 *keystate) {
	return;

}
void Coin::draw() {
	dest.x = position->x + 5 - data->camera.x;
	dest.y = position->y + 5- data->camera.y;
	data->texmanager.Draw(texture, src, dest, data->renderer);

}