#pragma once
#ifndef SRC_BOW_H_
#define SRC_BOW_H_
#include "SDL.h"
#include "Vector.h"
#include "Game.h"

class Bow {
public:

	Bow(GameDataRef data, float x, float y, float h, float w);
	~Bow() {}
	void loadtexture(const char* path, const char* name, int tilex, int tiley);
	void loadtexture(const char* name, int tilex, int tiley);
	void update(float dt, int x, int y);
	void handleinput(SDL_Event event);
	void draw();

private:
	int width;
	int height;
	Vector* position;

	int frames;
	int speed;
	bool animated;
	SDL_Rect src, dest;
	SDL_Texture* texture;
	GameDataRef data;
};

#endif /* SRC_BOW_H_ */