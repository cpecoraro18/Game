#include "Playerh.h"
#include "SDL.h"

Vector* gravity = new Vector(0, .05);
Vector* normal = new Vector(0, -.05);

Player::Player(float x, float y, int h, int w) {
	this->position = new Vector(x, y);
	this->velocity = new Vector();
	this->acceleration = new Vector();
	this->height = h;
	this->width = w;
	hitbox = new AABB(x, y, w, h);
	jumped = true;
	src.x = src.y = 0;
	src.h = 32;
	src.w = 32;
	dest.x = position->x;
	dest.y = position->y;
	dest.h = height;
	dest.w = width;
	
	

}


void Player::update(std::vector<class Entity*> &entities) {
	if (velocity->y != 0 && jumped == true) {
		//velocity->operator+=(*gravity);
	}
	

	

	if (hitbox->leftside < 0 || hitbox->rightside > 800) {
		position->operator-=(*velocity);
		velocity->x = 0;
	}
	if (hitbox->top < 0 || hitbox->bottom > 650) {
		position->operator-=(*velocity);
		velocity->y = 0;
	}
	position->x += velocity->x;
	position->y += velocity->y;
	hitbox->setDimentions(position->x, position->y);
	handleCollisions(entities);

}

void Player::handleCollisions(std::vector<class Entity*> &entities) {
	for (auto&& ent : entities) {
		if (ent != this && Collision::checkAABB(*hitbox, *(ent->hitbox))) {
			if (velocity->x > 0) {
				// collision occurred on the left
				position->operator-=(*velocity);
				velocity->x = 0;
			}
			else if (velocity->x < 0) {
				// collision occurred on the right
				position->operator-=(*velocity);
				velocity->x = 0;
			}
			if (velocity->y > 0) {
				// collision occurred on the bottom
				position->operator-=(*velocity);
				velocity->y = 0;
			}
			else if (velocity->y < 0) {
				// collision occurred on the top
				position->operator-=(*velocity);
				velocity->y = 0;
			}
		}
	}

}

void Player::loadtexture(const char* path, SDL_Renderer* ren) {
	this->texture = TextureManager::LoadTexture(path, ren);
}

void Player::draw(SDL_Renderer* ren) {
	dest.x = position->x;
	dest.y = position->y;

	TextureManager::Draw(texture, ren, src, dest);

}

void Player::handleinput(SDL_Event event) {

	if (event.type == SDL_KEYDOWN)
	{
		//Select surfaces based on key press
		switch (event.key.keysym.sym)
		{

		case SDLK_LEFT:
			goLeft();
			break;

		case SDLK_RIGHT:
			goRight();
			break;
		case SDLK_UP:
			velocity->y = -1;
			break;

		case SDLK_DOWN:
			velocity->y = 1;
			break;
		case SDLK_SPACE:
			jump();
			
			break;
		default:
			break;
		}
	}
	else if (event.type == SDL_KEYUP) {
		switch (event.key.keysym.sym)
		{
		case SDLK_LEFT:
			velocity->x = 0;
			break;
		case SDLK_RIGHT:
			velocity->x = 0;
			break;
		case SDLK_UP:
			velocity->y = 0;
			break;
		case SDLK_DOWN:
			velocity->y = 0;
			break;
		case SDLK_SPACE:
			velocity->y = 0;
			break;
		default:
			break;
		}

	}

}

void Player::goRight() {
	velocity->x = 1;

}

void Player::goLeft() {
	velocity->x = -1;
}

void Player::jump() {


}