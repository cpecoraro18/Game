#include "EndLevel.h"

EndLevel::EndLevel(GameDataRef data, float x, float y, float h, float w) : Entity(x, y, h, w, 1, 0, data) {
	type_ = kEndLevel;
	dead = false;
	hitbox = new AABB(x, y, w, h);
	src.x = 0;
	src.y = 0;
	src.h = 32;
	src.w = 32;
	destHitbox.x = x - data->camera.x;
	destHitbox.y = y - data->camera.y;
	destHitbox.w = w;
	destHitbox.h = h;
	animated = false;

}


EndLevel::~EndLevel() {

	//printf("Deleting Block\n"); 
	delete hitbox;

}



void EndLevel::draw() {
	dest.x = (int)position->x - data->camera.x;
	dest.y = (int)position->y - data->camera.y;
	destHitbox.x = position->x - data->camera.x;
	destHitbox.y = position->y - data->camera.y;

	data->texmanager.Draw(texture, src, dest, data->renderer);
	//data->texmanager.Draw(hitboxTexture, srcHitbox, destHitbox, data->renderer);
}

void EndLevel::update(std::vector<class Entity*>& collidables, float dt) {
	hitbox->setDimentions(position->x, position->y);
	return;
}
void EndLevel::handleinput(SDL_Event event, const Uint8* keystate) {
	return;
}

void EndLevel::handleCollisions(Player* player, int onx) {


}