#include "Knight.h"
Vector* knightmaxSpeed = new Vector(1, 15);


Knight::Knight(int x, int y, int h, int w, int nFrames, int frameSpeed, GameDataRef data) : Entity(x, y, h, w, nFrames, frameSpeed, data){
	type_ = kKnight;
	dead = false;
	src.x = 0;
	src.y = 0;
	src.h = 64;
	src.w = 64;
	hitbox = new AABB(x, y, w, h);
	texture = data->texmanager.GetTexture("knight");
	hitboxTexture = data->texmanager.GetTexture("hitbox");

	destHitbox.x = x - data->camera.x;
	destHitbox.y = y - data->camera.y;
	destHitbox.w = w;
	destHitbox.h = h;
	goLeft();

}


void Knight::update(std::vector<class Entity*> collidables, float dt, Player* player) {
	Entity::update(collidables, dt);

	position->x += velocity->x;
	hitbox->setDimentions(position->x, position->y);
	handleCollisions(collidables, 1, dt);
	position->y += velocity->y;
	hitbox->setDimentions(position->x, position->y);
	handleCollisions(collidables, 0, dt);

	if (velocity->x > knightmaxSpeed->x) {
		velocity->x = knightmaxSpeed->x;
	}
	else if (fabs(velocity->x) > knightmaxSpeed->x) {
		velocity->x = -1 * knightmaxSpeed->x;
	}

	if (velocity->y > knightmaxSpeed->y) {
		velocity->y = knightmaxSpeed->y;
	}
	else if (fabs(velocity->y) > knightmaxSpeed->y) {
		velocity->y = -1 * knightmaxSpeed->y;
	}

	if (hitbox->leftside < 0 || hitbox->rightside  > 5500) {
		position->x -= velocity->x;
		velocity->x = velocity->x*-1;
		acceleration->x = acceleration->x * -1;

	}
	
	if (position->x < player->position->x && abs(position->x - player->position->x) < 200) {
		attacking = false;
		goRight();
	}
	else if (position->x > player->position->x && abs(position->x - player->position->x) < 200) {
		attacking = false;
		goLeft();
	}

	if (abs(player->position->x - position->x) < 80) {
		acceleration->x = 0;
		velocity->x = 0;
		attacking = true;
	}
	
	if (animated) {
		Animate(player);
	}
	return;
}

void Knight::draw() {
	if (dead) {
		return;
	}
	dest.x = position->x - data->camera.x;
	dest.y = position->y - data->camera.y;
	destHitbox.x = position->x - data->camera.x;
	destHitbox.y = position->y - data->camera.y;

	data->texmanager.Draw(texture, src, dest, data->renderer);
	//data->texmanager.Draw(hitboxTexture, srcHitbox, destHitbox, data->renderer);

}

void Knight::handleCollisions() {
	health--;
	if (health < 0) {
		die();
	}
	
}

void Knight::handleCollisions(std::vector<class Entity*>& collidables, int onx, float dt) {
	for (auto&& ent : collidables) {

		if (ent != this && !ent->dead && Collision::checkAABB(*hitbox, *(ent->hitbox))) {
			switch (ent->type_) {
			case(kBlock):
				if (velocity->x > 0 && onx == 1) {
					// collision occurred on the right
					position->x -= velocity->x;
					velocity->x = velocity->x * -1;
					acceleration->x = acceleration->x * -1;
					//printf("Right");
					return;
				}
				if (velocity->x < 0 && onx == 1) {
					// collision occurred on the left
					position->x -= velocity->x;
					velocity->x = velocity->x * -1;
					acceleration->x = acceleration->x * -1;
					//printf("Left");
					return;
				}
				if (velocity->y > 0 && onx == 0) {
					// collision occurred on the bottom
					position->y -= velocity->y;
					velocity->y = 0;
					mOnGround = true;
					//printf("Bottom");
					return;

				}
				else {
					mOnGround = false;
				}
				if (velocity->y < 0 && onx == 0) {
					// collision occurred on the top
					position->y -= velocity->y;
					velocity->y = 0;
					//printf("Top");
					return;
				}
				break;
			case(kSpike):
				die();
				break;


			}

		}
	}

}
void Knight::Animate(Player* player) {
	//in air and moving right
	
	//moving right and on ground
	if (velocity->x > .5 && mOnGround) {
		speed = 100;
		//jumpSpriteCounter = 0;
		src.y = 128;
		frames = 4;
	}
	//moving left and on ground
	else if (velocity->x < -.5 && mOnGround) {
		speed = 100;
		//jumpSpriteCounter = 0;
		src.y = 192;
		frames = 4;
	}
	//not moving and on ground
	else if (mOnGround) {
		speed = 100;
		//jumpSpriteCounter = 0;
		src.y = 0;
		frames = 2;
	}

	if (attacking && player->position->x > position->x) {
		speed = 50;
		src.y = 256;
		frames = 5;
	} 
	else if (attacking && player->position->x < position->x) {
		speed = 50;
		src.y = 320;
		frames = 5;
	}

	if (attacking && src.x / 64 == 3) {
		
		//attack(player);

	}
	if (attacking && src.x / 64 == 4) {
		attacking = false;
	
	}
	
	Entity::Animate();
}

void Knight::goRight() {
	acceleration->x = 1.0f;

}

void Knight::goLeft() {
	acceleration->x = -1.0f;
}


void Knight::die() {
	dead = true;
}

void Knight::attack(Player* player) {
	if (player->position->x > position->x && player->position->x - position->x < 50) {
		player->die();
		
	}
	if (player->position->x < position->x&& player->position->x - position->x < -50) {
		player->die();
	}

}
