#include "Player.h"
#include "SDL.h"
#include "TextureManager.h"
#include "Map.h"
#include "Window.h"
#include <cmath>

Vector* gravity = new Vector(0, 1);
Vector* gFriction = new Vector(.85, 1);
Vector* aFriction = new Vector(.99, 1);
Vector* maxSpeed = new Vector(5, 15);

Player::Player(float x, float y, int h, int w) {
	this->position = new Vector(x, y);
	this->velocity = new Vector();
	this->acceleration = new Vector();
	this->height = h;
	this->width = w;
	hitbox = new AABB(x, y, w, h);
	mOnGround = false;
	groundFriction = false;
	airFriction = false;
	src.x = src.y = 0;
	src.h = 32;
	src.w = 32;
	dest.x = position->x - Window::camera.x;
	dest.y = position->y - Window::camera.y;
	dest.h = height;
	dest.w = width;
	count = 0;
	jumpCount = 0;




}


void Player::update(std::vector<class Entity*> &entities) {
	count++;

	velocity->operator+=(*gravity);
	
	velocity->operator+=(*acceleration);

	if (velocity->x > maxSpeed->x) {
		velocity->x = maxSpeed->x;
	}
	else if (abs(velocity->x) > maxSpeed->x) {
		velocity->x = -1* maxSpeed->x;
	}

	if (abs(velocity->y) > maxSpeed->y) {
		velocity->y = maxSpeed->y;
	}

	if (hitbox->leftside - Window::camera.x < 0 || hitbox->rightside - Window::camera.x > 800) {
		position->x -= velocity->x;
		velocity->x = 0;
	}
	if  (hitbox->bottom - Window::camera.y > 640) {
		position->y -= velocity->y;
		velocity->y = 0;
	}

	//change x position
	oldPosition = position;
	position->x += velocity->x;
	hitbox->setDimentions(position->x, position->y);
	handleCollisions(entities, 1);
	if (groundFriction) {
		velocity->operator*=(*gFriction);
	}
	
	
	//change y position
	oldPosition = position;
	position->y += velocity->y;
	hitbox->setDimentions(position->x, position->y);
	handleCollisions(entities, 0);
	if (count % 10 == 0) {
		//printf("X:%f  Y:%f\n", velocity->x, velocity->y);
	}

}

void Player::handleCollisions(std::vector<class Entity*> &entities, int onx) {
	for (auto&& ent : entities) {
		if (ent != this && Collision::checkAABB(*hitbox, *(ent->hitbox))) {
			if (velocity->x > 0 && onx == 1) {
				// collision occurred on the right
				position->x -= velocity->x;
				velocity->x = 0;
				handleCollisions(entities, onx);
				//printf("right");
			}
			if (velocity->x < 0 && onx == 1) {
				// collision occurred on the left
				position->x -= velocity->x;
				velocity->x = 0;
				handleCollisions(entities, onx);
				//printf("left");
			}
			if (velocity->y > 0 && onx == 0) {
				// collision occurred on the bottom
				position->y -= velocity->y;
				velocity->y = 0;
				mOnGround = true;
				jumpCount = 0;
				handleCollisions(entities, onx);
			}
			else {
				mOnGround = false;
			}
			if (velocity->y < 0 && onx == 0) {
				// collision occurred on the top
				position->y -= velocity->y;
				velocity->y = 0;
				handleCollisions(entities, onx);
			}
		}
	}

}


void Player::loadtexture(const char* path) {
	this->texture = TextureManager::LoadTexture(path);
}

void Player::draw() {
	dest.x = position->x-Window::camera.x;
	dest.y = position->y-Window::camera.y;

	TextureManager::Draw(texture, src, dest);

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
			break;
		default:
			break;
		}

	}

}

void Player::goRight() {
	acceleration->x = .5;
}

void Player::goLeft() {
	acceleration->x = -.5;
}

void Player::jump() {
	velocity->y = -15;
}