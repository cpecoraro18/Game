#pragma once
#ifndef SRC_PLAYERH_H_
#define SRC_PLAYERH_H_

#include "Entity.h"
#include "Map.h"



class Player: public Entity {
public:

	Player(float x, float y, int h, int w);

	~Player() {}

	void update(std::vector<class Entity*> &entities);

	void loadtexture(const char* path, SDL_Renderer* ren);
	
	void draw(SDL_Renderer* ren);

	void handleinput(SDL_Event event);

	void handleCollisions(std::vector<class Entity*> &entities);

	void goRight();

	void goLeft();

	void jump();
	
	Vector getPosition() { return *position; }
	

private:
	bool jumped;
	

};

#endif /* SRC_PLAYERH_H_ */
