#pragma once
#ifndef SRC_BLOCK_H_
#define SRC_BLOCK_H_
#include "SDL.h"
#include "TextureManager.h"
#include "Entity.h"

class Block : public Entity {
public:

	Block(float x, float y, float h, float w);
	~Block() {}

	void loadtexture(const char* path, SDL_Renderer* ren);
	void update(std::vector<class Entity*> &entities);
	void handleinput(SDL_Event event);
	void draw(SDL_Renderer* ren);


private:

	SDL_Rect src, dest;
	SDL_Texture* texture;
};



#endif /* SRC_BLOCK_H_ */