#include "Player.h"
#include "SDL.h"
#include "TextureManager.h"
#include "World.h"
#include "MapState.h"
#include <algorithm>

#include <cmath>


Vector* maxSpeed = new Vector(10, 30);

Player::Player(int x, int y, int h, int w, int nFrames, int frameSpeed, GameDataRef data) : Entity(x, y, h, w, nFrames, frameSpeed, data) {

	type_ = kPlayer;

	hitboxXBuffer = w * .25;
	hitboxYBuffer = h * .25;
	hitboxWidthBuffer = w * .66 * -1;
	hitboxHeightBuffer = h * .33 * -1;
	hitbox = new AABB(x + hitboxWidthBuffer, y + hitboxYBuffer, w + hitboxWidthBuffer, h + hitboxHeightBuffer);
	
	src.x = 0;
	src.y = 0;
	src.w = 32;
	src.h = 32;

	destHitbox.x = x + hitboxXBuffer - data->camera.x;
	destHitbox.y = y + hitboxYBuffer - data->camera.y;
	destHitbox.w = w + hitboxWidthBuffer;
	destHitbox.h = h + hitboxHeightBuffer;

	spawnPoint = new Vector(x, y);

	
	mOnGround = false;
	groundFriction = false;
	airFriction = false;

	count = 0;
	coinCount = 0;
	keyCount = 0;
	jumpCount = 0;
	jumpSpriteCounter = 0;

	shooting = false;
	armtexture = data->texmanager.GetTexture("armandbow");
	srcarm.x = 0;
	srcarm.y = 0;
	srcarm.h = 32;
	srcarm.w = 32;
	destarm.x = x + 7 - data->camera.x;
	destarm.y = y + 10 - data->camera.y;
	destarm.h = h;
	destarm.w = w;
	jumpSound = data->audioManager.GetChunk("jumpSound");
	bowSound = data->audioManager.GetChunk("bowSound");

	coinCounter = new CoinCounter(data);

	dead = false;
	deathCount = 0;


}

Player::~Player() {
	//printf("Destroying player\n");
	delete coinCounter;
	delete spawnPoint;

}



void Player::update(World* world) {
	if (!playing) {
		data->machine.AddState(StateRef(new MapState(data)));
	}


	if (dead) {
		if (deathCount == 0) {
			velocity->y = -20.0f;

		}
		deathCount++;
		if (deathCount > 120) {
			position->x = spawnPoint->x;
			position->y = spawnPoint->y;
			velocity->x = 0;
			velocity->y = 0;
			acceleration->x = 0;
			acceleration->y = 0;
			src.x = 0;
			src.y = 0;
			dead = false;
			deathCount = 0;
	
		}
		count++;
		Entity::update(world);
		//cap max speed
		if (velocity->x > maxSpeed->x) {
			velocity->x = maxSpeed->x;
		}
		else if (fabs(velocity->x) > maxSpeed->x) {
			velocity->x = -1 * maxSpeed->x;
		}

		if (velocity->y > maxSpeed->y) {
			velocity->y = maxSpeed->y;
		}
		else if (fabs(velocity->y) > maxSpeed->y) {
			velocity->y = -1 * maxSpeed->y;
		}
		Animate();
		position->y += velocity->y;
		hitbox->setDimentions(position->x + hitboxXBuffer, position->y + hitboxYBuffer);
		return;
	}
	
	
	count++;
	Entity::update(world);
	//cap max speed
	if (velocity->x > maxSpeed->x) {
		velocity->x = maxSpeed->x;
	}
	else if (fabs(velocity->x) > maxSpeed->x) {
		velocity->x = -1 * maxSpeed->x;
	}

	if (velocity->y > maxSpeed->y) {
		velocity->y = maxSpeed->y;
	}
	else if (fabs(velocity->y) > maxSpeed->y) {
		velocity->y = -1 * maxSpeed->y;
	}

	//handle edge of screen cases
	if (hitbox->leftside - data->camera.x < 0 || hitbox->rightside - data->camera.x > data->camera.w) {
		position->x -= velocity->x;
		velocity->x = velocity->x * -.5;

	}
	if (hitbox->bottom - data->camera.y > data->camera.h ) {
		die();
	}

	//animate
	Animate();




	//change x position
	position->x += velocity->x;
	hitbox->setDimentions(position->x + hitboxXBuffer, position->y + hitboxYBuffer);
	handleCollisions(world->collidables, 1);

	//handle friction
	if (groundFriction) {
		velocity->x *= .85;
	}
	else {
		velocity->x *= .95;
	}
	//change y position
	position->y += velocity->y;
	hitbox->setDimentions(position->x + hitboxXBuffer, position->y + hitboxYBuffer);
	handleCollisions(world->collidables, 0);
	
	//update arrows
	for (int i = 0; i < arrows.size(); i++) {
		arrows[i]->update(world);
		coinCount += arrows[i]->getNumCoinsHit();
		keyCount += arrows[i]->getNumKeysHit();
		if (arrows[i]->dead) {
			arrows.erase(arrows.begin() + i);
			
		}

	}
	//update coin observer
	coinCounter->Notify(coinCount);
	
}

void Player::handleCollisions(std::vector<class Entity*>& collidables, int onx) {
	int buffer = 100;
	for (auto&& ent : collidables) {
		//check if on screen
		if (ent->position->x >= data->camera.x - buffer && ent->position->x + ent->width <= data->camera.x + data->camera.w + buffer &&
			ent->position->y >= data->camera.y - buffer && ent->position->y + ent->height <= data->camera.y + data->camera.h + buffer) {
			if (ent != this && !ent->dead && Collision::checkAABB(*hitbox, *(ent->hitbox))) {
				switch (ent->type_) {
				case(kBlock):
					if (velocity->x > 0 && onx == 1) {
						// collision occurred on the right
						position->x -= velocity->x;
						velocity->x = velocity->x * -.4;
						//printf("Right");
						return;
					}
					if (velocity->x < 0 && onx == 1) {
						// collision occurred on the left
						position->x -= velocity->x;
						velocity->x = velocity->x * -.4;
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
					ent->handleCollisions();
					ent->dead = true;
					break;
				case(kKey):
					keyCount++;
					//printf("Coint count: %d\n", coinCount);
					ent->handleCollisions();
					break;
				case(kSpike):
					die();
					break;
				case(kEndLevel):
					playing = false;
					
				}


			}

		}
		
	}

}

void Player::Animate() {
	//in air and moving right
	if (fabs(velocity->y) > 1 && velocity->x > 0.5) {
		if (jumpSpriteCounter == 0) {
			src.x = 0;
		}
		jumpSpriteCounter++;
		src.y = 32*4;
		frames = 3;
		speed = 200;
	}
	//in air and moving left
	else if (fabs(velocity->y) > 1 && velocity->x < -0.5) {
		if (jumpSpriteCounter == 0) {
			src.x = 0;
		}
		jumpSpriteCounter++;
		src.y = 32*5;
		frames = 3;
		speed = 200;
	}
	//in air and not moving on x axis
	else if (fabs(velocity->y) > 1.5  && fabs(velocity->x) < 0.5) {
		if (jumpSpriteCounter == 0) {
			src.x = 0;
		}
		jumpSpriteCounter++;
		src.y = 96;
		frames = 3;
		speed = 200;
	}
	//moving right and on ground
	else if (velocity->x > .5 && mOnGround) {
		speed = 100;
		jumpSpriteCounter = 0;
		src.y = 32*1;
		frames = 4;
	}
	//moving left and on ground
	else if (velocity->x < -.5 && mOnGround) {
		speed = 100;
		jumpSpriteCounter = 0;
		src.y = 32*2;
		frames = 4;
	}
	//not moving and on ground
	else if (mOnGround) {
		speed = 100;
		jumpSpriteCounter = 0;
		src.y = 32*0;
		frames = 3;
	}
	//shooting animations
	if (shooting) {
		//calculate bow angle
		double dy = mouseY - (position->y - data->camera.y);
		double dx = mouseX - (position->x - data->camera.x);
		double theta = atan2(dy, dx);
		angle = ((theta * 180) / M_PI);

		if (dx > 0) {
			shootingRight = true;
			shootingLeft = false;
		}
		else {
			shootingLeft = true;
			shootingRight = false;
		}

		if (abs(velocity->x) > 0.5 && mOnGround && shootingRight) {
			speed = 100;
			src.y = 32*8;
			frames = 4;
		}
		else if (abs(velocity->x) > 0.5 && mOnGround && shootingLeft) {
			speed = 100;
			src.y = 32*9;
			frames = 4;
		}
		else {
			if (shootingRight) {
				src.x = 0;
				src.y = 32*6;
				srcarm.x = 0;
				srcarm.y = 0;
				armFrames = 7;
				armSpeed = 200;

			}
			else if (shootingLeft) {
				src.x = 0;
				src.y = 32*7;
				srcarm.x = 0;
				srcarm.y = 32;
				armFrames = 7;
				armSpeed = 200;
			}
			frames = 1;
		}
	}

	if (dead) {
		src.y = 32 * 10;
		frames = 1;
	}

	if (jumpSpriteCounter >  8) {
		src.x = src.w*(frames-1);
		return;
	}
	Entity::Animate();
	if (srcarm.x != 7) {
		srcarm.x = srcarm.w * static_cast<int>((SDL_GetTicks() / armSpeed) % armFrames);
	}
	
}


void Player::draw() {
	dest.x = position->x-data->camera.x;
	dest.y = position->y-data->camera.y;
	if (shootingRight) {
		destarm.x = position->x + 7 - data->camera.x;
	}
	if (shootingLeft) {
		destarm.x = position->x - 7 - data->camera.x;
	}
	
	destarm.y = position->y - data->camera.y;

	data->texmanager.Draw(texture, src, dest, data->renderer);
	//data->texmanager.Draw(hitboxTexture, srcHitbox, destHitbox, data->renderer);
	if (shootingRight && shooting) {
		data->texmanager.Draw(armtexture, srcarm, destarm, data->renderer, angle);
	} if (shootingLeft && shooting) {
		data->texmanager.Draw(armtexture, srcarm, destarm, data->renderer, angle-180);
	}

	for (auto &arrow : arrows) {
		arrow->draw();
	}

	coinCounter->Display();
}

void Player::handleinput(SDL_Event event, const Uint8 *keystate) {
	if (dead) {
		return;
	}
	SDL_GetMouseState(&mouseX, &mouseY);
	if (event.type == SDL_MOUSEBUTTONDOWN) {
		shooting = true;
		
	}
	if (event.type == SDL_MOUSEBUTTONUP) {
		double dy = mouseY - (position->y - data->camera.y);
		double dx = mouseX - (position->x - data->camera.x);
		double theta = atan2(dy, dx);
		shoot(cos(theta)*shootSpeed, sin(theta)*shootSpeed);
		shooting = false;
	}

	if (event.type == SDL_KEYDOWN)
	{
		//Select surfaces based on key press
		switch (event.key.keysym.sym)
		{

		case SDLK_a:
			groundFriction = false;
			goLeft();
			break;
		case SDLK_d:
			groundFriction = false;
			goRight();
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
	if (event.type == SDL_KEYUP) {
		switch (event.key.keysym.sym)
		{
		case SDLK_a:
			acceleration->x = 0.0f;
			groundFriction = true;
			break;
		case SDLK_d:
			acceleration->x = 0.0f;
			groundFriction = true;
			break;
		case SDLK_SPACE:
			if (velocity->y < 0) {
				velocity->y *= .3;
			}
			break;
		default:
			break;
		}
	}

	if (keystate[SDL_SCANCODE_A]) {
		goLeft();
	}
	if (keystate[SDL_SCANCODE_D]) {
		goRight();
	}
}

void Player::goRight() {
	
	acceleration->x = moveSpeed;
}

void Player::goLeft() {
	acceleration->x = -1* moveSpeed;
}

void Player::jump() {
	jumpSpriteCounter = 0;
	velocity->y = jumpVelocity;
	Mix_PlayChannel(-1, jumpSound, 0);
}

void Player::die() {
	if (!dead) {
		src.y = 32 * 10;
		frames = 1;
		dead = true;
	}
	
	
}

void Player::shoot(float speedx, float speedy) {
	Arrow* arrow = new Arrow(data, position->x + 10, position->y + 10, BLOCK_SIZE, BLOCK_SIZE, speedx, speedy-2);
	arrow->loadHitboxTexture("hitbox", 0, 0);
	arrows.emplace_back(arrow);
	Mix_PlayChannel(-1, bowSound, 0);
	srcarm.x = 0;

}

void Player::aim() {
	src.x = 32;
	src.y = 0;
}