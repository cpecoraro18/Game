#pragma once
#ifndef SRC_SPLASHSTATE_H_
#define SRC_SPLASHSTATE_H_
#include "SDL.h"
#include "SDL_image.h"
#include "Game.h"


class SplashState : public State {
public:
	SplashState(GameDataRef data);

	bool Init();

	void HandleInput();
	void Update(float dt);
	void Draw();

private:
	GameDataRef data;
	SDL_Texture *_background;
	SDL_Rect src, dest;
};

#endif /* SRC_SPLASHSTATE_H_ */