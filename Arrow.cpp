#include "Arrow.h"
#include "Entity_type.h"


#include <iostream>

Vector* arrowgravity = new Vector(0, .5);
Arrow::Arrow(GameDataRef data, float x, float y, float h, float w, float speedx, float speedy) : data(data) {
	this->position = new Vector(x , y);
	this->velocity = new Vector(speedx, speedy-5);
	this->height = h;
	this->width = w;

	hitboxXBuffer = 15;
	hitboxYBuffer = 20;
	hitboxWidthBuffer =  -30;
	hitboxHeightBuffer = -40;

	hitbox = new AABB(x + hitboxXBuffer, y + hitboxYBuffer, w + hitboxWidthBuffer, h + hitboxHeightBuffer);
	srcHitbox.x = 0;
	srcHitbox.y = 0;
	srcHitbox.h = 32;
	srcHitbox.w = 32;
	destHitbox.x = x + hitboxXBuffer - data->camera.x;
	destHitbox.y = y + hitboxYBuffer - data->camera.y;
	destHitbox.w = w + hitboxWidthBuffer;
	destHitbox.h = h + hitboxHeightBuffer;

	src.x = src.y = 0;
	dest.x = x - data->camera.x;
	dest.y = y - data->camera.x;
	dest.h = h;
	dest.w = w;
	src.h = 32;
	src.w = 32;
	frames = 1;
	speed = 100;
	count = 0;
	numCoinsHit = 0;
	stuck = false;
	dead = false;
	loadtexture("arrow", 0, 0);
}

Arrow::~Arrow() {
	//printf("Deleting Arrow\n");
	delete position;
	delete velocity;
	delete hitbox;

}


void Arrow::draw() {
	if (dead) {
		return;
	}
	dest.x = position->x - data->camera.x;
	dest.y = position->y - data->camera.y;
	destHitbox.x = position->x + hitboxXBuffer - data->camera.x;
	destHitbox.y = position->y + hitboxYBuffer - data->camera.y;

	if (!stuck) {
		double theta = atan2(velocity->y, velocity->x);
		angle = ((theta * 180) / M_PI);
	}
	data->texmanager.Draw(texture, src, dest, data->renderer, angle);
	//data->texmanager.Draw(hitboxTexture, srcHitbox, destHitbox, data->renderer);
}

void Arrow::update(std::vector<class Entity*> collidables, std::vector<class Entity*> enemies, float dt) {
	count++;
	
	if (count > 1000) {
		dead = true;
	}

	if (stuck) {
		return;
	}
	velocity->x += arrowgravity->x;
	velocity->y += arrowgravity->y;

	position-> x += velocity->x;
	position->y += velocity->y;
	hitbox->setDimentions(position->x+hitboxXBuffer, position->y + hitboxYBuffer);
	handleCollisions(collidables);
	handleCollisions(enemies);
	//src.x = src.w*static_cast<int>((SDL_GetTicks() / speed) % frames);
	return;
}

void Arrow::handleCollisions(std::vector<class Entity*> collidables) {
	double theta;
	for (auto&& ent : collidables) {

		if ( !ent->dead && Collision::checkAABB(*hitbox, *(ent->hitbox))) {
			switch (ent->type_) {
			case(kBlock):
				stuck = true;
				theta = atan2(velocity->y, velocity->x);
				angle = ((theta * 180) / M_PI);
				if (velocity->x > 0) {
					// collision occurred on the right
					//position->x -= velocity->x;
					velocity->x = 0;
					velocity->y = 0;
					//printf("Right");
					return;
				}
				if (velocity->x < 0 ) {
					// collision occurred on the left
					//position->x -= velocity->x;
					velocity->x = 0;
					velocity->y = 0;
					//printf("Left");
					return;
				}
				if (velocity->y > 1 ) {
					// collision occurred on the bottom
					//position->y -= velocity->y;
					velocity->x = 0;
					velocity->y = 0;
					//printf("Bottom");
					return;

				}
				if (velocity->y < 0) {
					// collision occurred on the top
					//position->y -= velocity->y;
					velocity->x = 0;
					velocity->y = 0;
					//printf("Top");
					return;
				}
				break;
			case(kCoin):
				numCoinsHit++;
				//printf("Coint count: %d\n", coinCount);
				ent->handleCollisions();
				ent->dead = true;
				break;
			case(kBird):
				ent->handleCollisions();
				break;
			case(kKnight):
				ent->handleCollisions();
				break;
			/*case(kKey):
				keyCount++;
				//printf("Coint count: %d\n", coinCount);
				ent->handleCollision();
				break;
			case(kSpike):
				die();
				break;*/


			}

		}
	}

}
void Arrow::handleinput(SDL_Event event) {
	return;
}

int Arrow::getNumCoinsHit() {
	int coins = numCoinsHit;
	numCoinsHit = 0;
	return coins;
}

void Arrow::loadtexture(const char* name, int tilex, int tiley) {
	texture = data->texmanager.GetTexture(name);
	src.x = tilex;
	src.y = tiley;

}
void Arrow::loadHitboxTexture(const char* name, int tilex, int tiley) {

	hitboxTexture = data->texmanager.GetTexture(name);
}
