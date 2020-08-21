#include "Block.h"
#include "TextureManager.h"
#include <iostream>

Block::Block(GameDataRef data, float x, float y, float h, float w): Entity(x, y, h, w, 1, 0, data) {
	type_ = kBlock;
	dead = false;
	hitbox = new AABB(x, y, w, h);
	src.x = 0;
	src.y = 0;
	src.h = 32;
	src.w = 32;
	destHitbox.x = x - data->camera.x;
	destHitbox.y = y  - data->camera.y;
	destHitbox.w = w;
	destHitbox.h = h;
	animated = false;

}

Block::Block(GameDataRef data, float x, float y, float h, float w, int nFrames, int frameSpeed) : Entity(x, y, h, w, nFrames, frameSpeed, data)  {
	type_ = kBlock;
	dead = false;
	hitbox = new AABB(x, y, w, h);
	destHitbox.x = x - data->camera.x;
	destHitbox.y = y - data->camera.y;
	destHitbox.w = w;
	destHitbox.h = h;

}
Block::~Block() { 
	
	//printf("Deleting Block\n"); 
	delete hitbox;

}



void Block::draw() {
	dest.x = (int)position->x - data->camera.x;
	dest.y = (int)position->y - data->camera.y;
	destHitbox.x = position->x -data->camera.x;
	destHitbox.y = position->y -data->camera.y;

	data->texmanager.Draw(texture, src, dest, data->renderer);
	//data->texmanager.Draw(hitboxTexture, srcHitbox, destHitbox, data->renderer);
}

void Block::update(World* world) {
	hitbox->setDimentions(position->x, position->y );
	if (animated) {
		Entity::Animate();
	}
	return;
}
void Block::handleinput(SDL_Event event, const Uint8 *keystate) {
	return;
}

void Block::handleCollisions(Player* player, int onx) {
	

}