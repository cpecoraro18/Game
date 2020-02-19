#pragma once
#ifndef SRC_RENDERCOMPONENT_H_
#define SRC_RENDERCOMPONENT_H_

#include "Component.h"
#include "SDL.h"
#include "Game.h"

class RenderComponent : public Component {
public:
	RenderComponent(int srcx, int srcy, int srcw, int srch, int destx, int desty, int destw, int desth, int nFrames, int frameSpeed, const char* tex, GameDataRef data);
	RenderComponent() {}

	void Update();
	void Draw(int angle = 0);

	SDL_Rect src, dest;
	int frames;
	int speed;
private:
	
	SDL_Texture* texture;
	GameDataRef data;

	bool animated;

	
};

#endif /* SRC_RENDERCOMPONENT_H_ */