#include "Knight.h"
Vector* knightmaxSpeed = new Vector(3, 30);


Knight::Knight(int x, int y, int h, int w, int nFrames, int frameSpeed, GameDataRef data) : Enemy(x, y, h, w, nFrames, frameSpeed, data){
	type_ = kKnight;
	dead = false;
	src.x = 0;
	src.y = 0;
	src.h = 64;
	src.w = 64;
	hitboxXBuffer = w * .33;
	hitboxYBuffer = h * .25;
	hitboxWidthBuffer = w * .66 * -1;
	hitboxHeightBuffer = h * .25 * -1;
	hitbox = new AABB(x + hitboxXBuffer, y + hitboxYBuffer, w + hitboxWidthBuffer, h + hitboxHeightBuffer);
	texture = data->texmanager.GetTexture("knight");
	destHitbox.x = x + hitboxXBuffer- data->camera.x;
	destHitbox.y = y + hitboxYBuffer- data->camera.y;
	destHitbox.w = w + hitboxWidthBuffer;
	destHitbox.h = h + hitboxHeightBuffer;

	attacking = false;

}

Knight::~Knight() { 
	//printf("Deleting Knight\n");
	delete hitbox;
}


void Knight::update(World* world) {
	Entity::update(world);
	position->x += velocity->x;
	hitbox->setDimentions(position->x+hitboxXBuffer, position->y + hitboxYBuffer);
	handleCollisions(world->collidables, 1);
	position->y += velocity->y;
	hitbox->setDimentions(position->x + hitboxXBuffer, position->y + hitboxYBuffer);
	handleCollisions(world->collidables, 0);

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

	if (hitbox->leftside - data->camera.x < 0 || hitbox->rightside - data->camera.x > data->camera.w) {
		position->x -= velocity->x;
		velocity->x = velocity->x*-1;
		acceleration->x = acceleration->x * -1;

	}
	
	if (position->x < world->player->position->x && abs(position->x - world->player->position->x) < 1000 && abs(position->y - world->player->position->y) < 200) {
		attacking = false;
		goRight();
	}
	else if (position->x > world->player->position->x && abs(position->x - world->player->position->x) < 1000 && abs(position->y - world->player->position->y) < 200) {
		attacking = false;
		goLeft();
	}

	if (abs(world->player->position->x - position->x)< 45 ) {
		acceleration->x = 0;
		velocity->x = 0;
		attacking = true;
	}
	
	if (animated) {
		Animate(world->player);
	}
	return;
}

void Knight::draw() {
	if (dead) {
		return;
	}
	dest.x = position->x - data->camera.x;
	dest.y = position->y - data->camera.y;
	destHitbox.x = position->x +hitboxXBuffer - data->camera.x;
	destHitbox.y = position->y + hitboxYBuffer - data->camera.y;

	data->texmanager.Draw(texture, src, dest, data->renderer);
	//data->texmanager.Draw(hitboxTexture, srcHitbox, destHitbox, data->renderer);

}

void Knight::handleCollisions() {
	health--;
	if (velocity->y == 0) {
		velocity->y -= 3;
	}

	velocity->x = velocity->x *-4;
	acceleration->x = acceleration->x * -2;
	if (health < 0) {
		die();
	}
	
}

void Knight::handleCollisions(std::vector<class Entity*>& collidables, int onx) {
	for (auto&& ent : collidables) {

		if (ent != this && !ent->dead && Collision::checkAABB(*hitbox, *(ent->hitbox))) {
			switch (ent->type_) {
			case(kBlock):
				if (velocity->x > 0 && onx == 1) {
					// collision occurred on the right
					position->x -= velocity->x;
					velocity->x = velocity->x * -1;
					acceleration->x = acceleration->x * -1;
					printf("Right");
					return;
				}
				if (velocity->x < 0 && onx == 1) {
					// collision occurred on the left
					position->x -= velocity->x;
					velocity->x = velocity->x * -1;
					acceleration->x = acceleration->x * -1;
					printf("Left");
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
					printf("Top");
					return;
				}
				break;
			case(kSpike):
				//die();
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
		
		attack(player);

	}
	if (attacking && src.x / 64 == 4) {
		attacking = false;
	
	}
	
	Entity::Animate();
}

void Knight::goRight() {
	acceleration->x = 2.0f;

}

void Knight::goLeft() {
	acceleration->x = -2.0f;
}


void Knight::die() {
	dead = true;
}

void Knight::attack(Player* player) {
	if (Collision::checkAABB(*hitbox, *(player->hitbox))) {
		player->die();
	}
}
