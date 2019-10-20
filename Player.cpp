#include "Player.h"
#include "SDL.h"
#include "TextureManager.h"
#include "Map.h"
#include "Window.h"
#include <cmath>

Vector* gravity = new Vector(0, 1.0);
Vector* gFriction = new Vector(.85, 1.0);
Vector* aFriction = new Vector(.99, 1.0);
Vector* maxSpeed = new Vector(5.0, 15.0);

Player::Player(float x, float y, int h, int w, int nFrames, int frameSpeed) {
	this->position = new Vector(x, y);
	this->velocity = new Vector();
	this->acceleration = new Vector();
	this->height = h;
	this->width = w;
	hitbox = new AABB(x+15, y, w-30, h);
	
	mOnGround = false;
	groundFriction = false;
	airFriction = false;

	animated = true;
	frames = nFrames;
	speed = frameSpeed;
	src.x = 32;
	src.y = 0;
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

	if (animated) {
		if (fabs(velocity->y) > .75 && velocity->x > 0.5) {
			src.y = 96;
			frames = 1;
		}
		else if (fabs(velocity->y) > .75 && velocity->x < -0.5) {
			src.y = 128;
			frames = 1;
		}
		else if (fabs(velocity->y) > .75 && fabs(velocity->x) < 0.5){
			src.y = 160;
			frames = 1;
		}
		else if (velocity->x > .5 && mOnGround) {
			src.y = 32;
			frames = 8;
		}
		else if (velocity->x < -.5 && mOnGround) {
			src.y = 64;
			frames = 8;
		}
		else if(mOnGround){
			src.y = 0;
			frames = 3;
		}
		src.x = src.w*static_cast<int>((SDL_GetTicks() / speed) % frames);

	}

	if (count % 5 == 0) {
		//printf("X:%f  Y:%f\n", velocity->x, velocity->y);
	}
	velocity->operator+=(*gravity);
	
	velocity->operator+=(*acceleration);

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

	if (hitbox->leftside - Window::camera.x < 0 || hitbox->rightside - Window::camera.x > 800) {
		position->x -= velocity->x;
		velocity->x = velocity->x * -.5;
	}
	if  (hitbox->bottom - Window::camera.y > 640) {
		position->y -= velocity->y;
		velocity->y = 0;
	}

	//change x position
	oldPosition = position;
	position->x += velocity->x;
	hitbox->setDimentions(position->x+15, position->y);
	handleCollisions(entities, 1);
	if (groundFriction) {
		velocity->operator*=(*gFriction);
	}
	
	
	//change y position
	oldPosition = position;
	position->y += velocity->y;
	hitbox->setDimentions(position->x+15, position->y);
	handleCollisions(entities, 0);
	

}

void Player::handleCollisions(std::vector<class Entity*> &entities, int onx) {
	for (auto&& ent : entities) {
		if (ent != this && Collision::checkAABB(*hitbox, *(ent->hitbox))) {
			if (velocity->x > 0 && onx == 1) {
				// collision occurred on the right
				position->x -= velocity->x;
				velocity->x = velocity->x*-.4;
				return;
			}
			if (velocity->x < 0 && onx == 1) {
				// collision occurred on the left
				position->x -= velocity->x;
				velocity->x = velocity->x* -.4;
				return;
			}
			if (velocity->y > 0 && onx == 0) {
				// collision occurred on the bottom
				position->y -= velocity->y;
				velocity->y = 0;
				mOnGround = true;
				jumpCount = 0;
				return;
				
			}
			else {
				mOnGround = false;
			}
			if (velocity->y < 0 && onx == 0) {
				// collision occurred on the top
				position->y -= velocity->y;
				velocity->y = 0;
				return;
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