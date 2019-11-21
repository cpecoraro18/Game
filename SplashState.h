#pragma once
#ifndef SRC_SPLASHSTATE_H_
#define SRC_SPLASHSTATE_H_
#include "SDL.h"
#include "SDL_image.h"
#include "Game.h"


class SplashState : public State {
public:
	SplashState(GameDataRef data);
	~SplashState();

	void Identify() { printf("Splash State"); }
	bool Init();

	void HandleInput();
	void Update(float dt);
	void Draw();

private:
	GameDataRef data;
	SDL_Texture *_background;
	SDL_Rect src, dest;
	int count = 0;
};

#endif /* SRC_SPLASHSTATE_H_ */