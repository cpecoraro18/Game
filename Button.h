#pragma once
#ifndef SRC_BUTTON_H_
#define SRC_BUTTON_H_
#include "SDL.h"
#include "Game.h"

class Button  {
public:

	Button(GameDataRef data, float x, float y, float w, float h);
	Button(GameDataRef data, float x, float y, float w, float h, int nFrames, int frameSpeed);
	~Button() {}
	void loadtexture(const char* path, const char* name, int tilex, int tiley);
	void loadtexture(const char* name, int tilex, int tiley);
	void update();
	void draw();
	void handleClick();
	


	SDL_Rect src, dest;
	bool hovering;

private:
	
	SDL_Texture* texture;
	GameDataRef data;
	int width;
	int height;
	int x, y;
	
	bool animated;
	int frames;
	int speed;
};

#endif /* SRC_BUTTON_H_ */