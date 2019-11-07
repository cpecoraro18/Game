#pragma once
#ifndef SRC_MENUSTATE_H_
#define SRC_MENUSTATE_H_
#include "SDL.h"
#include "SDL_image.h"
#include "Game.h"


class MenuState : public State {
public:
	MenuState(GameDataRef data);

	bool Init();

	void HandleInput();
	void Update(float dt);
	void Draw();

private:
	GameDataRef data;
	SDL_Texture *_background;
	SDL_Rect backgsrc, backgdest;
};

#endif /* SRC_MENUSTATE_H_ */