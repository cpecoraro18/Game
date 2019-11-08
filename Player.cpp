#include "Player.h"
#include "SDL.h"
#include "TextureManager.h"
#include "Map.h"
#include <cmath>

Vector* gravity = new Vector(0, 15);
Vector* gFriction = new Vector(.90, 1.0);
Vector* aFriction = new Vector(.99, 1.0);
Vector* maxSpeed = new Vector(2.0, 10.0);


Player::Player(float x, float y, int h, int w, int nFrames, int frameSpeed, GameDataRef data): data(data) {
	type_ = kPlayer;
	this->position = new Vector(x, y);
	this->velocity = new Vector();
	this->acceleration = new Vector();
	this->height = h;
	this->width = w;
	hitbox = new AABB(x+25, y-25, w - 55, h-30);
	srcHitbox.x = 0;
	srcHitbox.y = 0;
	srcHitbox.h = 32;
	srcHitbox.w = 32;
	destHitbox.x = x + 25 - data->camera.x;
	destHitbox.y = y -25- data->camera.y;
	destHitbox.w = w - 60;
	destHitbox.h = h - 30;
	mOnGround = false;
	groundFriction = false;
	airFriction = false;

	animated = true;
	frames = nFrames;
	speed = frameSpeed;
	src.x = 0;
	src.y = 0;
	src.h = 32;
	src.w = 32;
	dest.x = position->x - data->camera.x;
	dest.y = position->y - data->camera.y;
	dest.h = height;
	dest.w = width;
	count = 0;
	coinCount = 0;
	jumpCount = 0;
	jumpSpriteCounter = 0;

}



void Player::update(std::vector<class Entity*> collidables, float dt) {
	//printf("%f\n", dt);
	count++;

	if (animated) {
		animate();

	}

	if (count % 50 == 0) {
		//printf("X:%f  Y:%f\n", velocity->x, velocity->y);
		
	}
	velocity->x += gravity->x * dt;
	velocity->y += gravity->y * dt;
	velocity->x += acceleration->x * dt;
	velocity->y += acceleration->y * dt;

	if (velocity->x > maxSpeed->x) {
		velocity->x = maxSpeed->x;
	}
	else if (fabs(velocity->x) > maxSpeed->x) {
		velocity->x = -1* maxSpeed->x;
	}

	if (velocity->y > maxSpeed->y) {
		velocity->y = maxSpeed->y;
	}
	else if (fabs(velocity->y) > maxSpeed->y) {
		velocity->y = -1 * maxSpeed->y;
	}

	if (hitbox->leftside - data->camera.x < 0 || hitbox->rightside - data->camera.x > 800) {
		position->x -= velocity->x;
		velocity->x = velocity->x * -.5;
	}
	if  (hitbox->bottom - data->camera.y > 640) {
		die();

	}

	//change x position
	oldPosition = position;
	position->x += velocity->x;
	hitbox->setDimentions(position->x+25, position->y+25);
	handleCollisions(collidables, 1);
	if (groundFriction) {
		velocity->operator*=(*gFriction);
	}
	
	
	//change y position
	oldPosition = position;
	position->y += velocity->y;
	hitbox->setDimentions(position->x + 25, position->y + 25);
	handleCollisions(collidables, 0);
	

}

void Player::handleCollisions(std::vector<class Entity*> &collidables, int onx) {
	for (auto&& ent : collidables) {

		if (ent != this && !ent->dead && Collision::checkAABB(*hitbox, *(ent->hitbox))) {
			switch (ent->type_) {
			case(kBlock):
				if (velocity->x > 0 && onx == 1) {
					// collision occurred on the right
					position->x -= velocity->x;
					velocity->x = velocity->x*-.4;
					//printf("Right");
					return;
				}
				if (velocity->x < 0 && onx == 1) {
					// collision occurred on the left
					position->x -= velocity->x;
					velocity->x = velocity->x* -.4;
					//printf("Left");
					return;
				}
				if (velocity->y > 0 && onx == 0) {
					// collision occurred on the bottom
					position->y -= velocity->y;
					velocity->y = 0;
					mOnGround = true;
					jumpCount = 0;
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
			case(kCoin):
				coinCount++;
				//printf("Coint count: %d\n", coinCount);
				ent->handleCollision();
				ent->dead = true;
				break;
			case(kKey):
				keyCount++;
				//printf("Coint count: %d\n", coinCount);
				ent->handleCollision();
				break;
			case(kSpike):
				die();
				break;
				

			}
			
		}
	}

}

void Player::animate() {
	if (fabs(velocity->y) > 1 && velocity->x > 0.5) {
		if (jumpSpriteCounter == 0) {
			src.x = 0;
		}
		jumpSpriteCounter++;
		src.y = 128;
		frames = 3;
		speed = 200;
	}
	else if (fabs(velocity->y) > 1 && velocity->x < -0.5) {
		if (jumpSpriteCounter == 0) {
			src.x = 0;
		}
		jumpSpriteCounter++;
		src.y = 160;
		frames = 3;
		speed = 200;
	}
	else if (fabs(velocity->y) > 1.5  && fabs(velocity->x) < 0.5) {
		if (jumpSpriteCounter == 0) {
			src.x = 0;
		}
		jumpSpriteCounter++;
		src.y = 96;
		frames = 3;
		speed = 200;
	}
	else if (velocity->x > .5 && mOnGround) {
		speed = 100;
		jumpSpriteCounter = 0;
		src.y = 32;
		frames = 4;
	}
	else if (velocity->x < -.5 && mOnGround) {
		speed = 100;
		jumpSpriteCounter = 0;
		src.y = 64;
		frames = 4;
	}
	else if (mOnGround) {
		speed = 100;
		jumpSpriteCounter = 0;
		src.y = 0;
		frames = 3;
	}
	if (jumpSpriteCounter >  8) {
		src.x = src.w*(frames-1);
		return;
	}
	src.x = src.w*static_cast<int>((SDL_GetTicks() / speed) % frames);
}

void Player::loadtexture(const char* path, const char* name, int tilex, int tiley) {
	data->texmanager.LoadTexture(path, name, data->renderer);
	texture = data->texmanager.GetTexture(name);

}

void Player::loadtexture(const char* name, int tilex, int tiley) {
	texture = data->texmanager.GetTexture(name);

}

void Player::loadHitboxTexture(const char* name, int tilex, int tiley) {
	this->hitboxTexture = data->texmanager.GetTexture(name);
}
void Player::draw() {
	dest.x = position->x-data->camera.x;
	dest.y = position->y-data->camera.y;
	destHitbox.x = position->x + 25 - data->camera.x;
	destHitbox.y = position->y + 25- data->camera.y;

	data->texmanager.Draw(texture, src, dest, data->renderer);
	//TextureManager::Draw(hitboxTexture, srcHitbox, destHitbox);

}

void Player::handleinput(SDL_Event event) {

	if (event.type == SDL_KEYDOWN)
	{
		//Select surfaces based on key press
		switch (event.key.keysym.sym)
		{

		case SDLK_LEFT:
			groundFriction = false;
			goLeft();
			break;
		case SDLK_RIGHT:
			groundFriction = false;
			goRight();
			break;
		case SDLK_DOWN:
			break;
		case SDLK_UP:
			break;
		case SDLK_SPACE:
			if (jumpCount < 2) {
				jumpCount++;
				jump();
			}
			mOnGround = false;
			break;
		default:
			break;
		}
	}
	else if (event.type == SDL_KEYUP) {
		switch (event.key.keysym.sym)
		{
		case SDLK_LEFT:
			acceleration->x = 0;
			groundFriction = true;
			break;
		case SDLK_RIGHT:
			acceleration->x = 0;
			groundFriction = true;
			break;
		case SDLK_DOWN:
			velocity->y = 0;
			break;
		case SDLK_UP:
			velocity->y = 0;
			break;
		case SDLK_SPACE:
			if (velocity->y < 0) {
				velocity->y *= .4;
			}
			
			break;
		default:
			break;
		}

	}

}

void Player::goRight() {
	
	acceleration->x = 7;
}

void Player::goLeft() {
	acceleration->x = -7;
}

void Player::jump() {
	jumpSpriteCounter = 0;
	velocity->y = -4.5;
}

void Player::die() {
	position->y -= velocity->y;
	velocity->y = 0;
	position->x = 50;
	position->y = 500;
}