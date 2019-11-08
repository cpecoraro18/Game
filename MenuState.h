#pragma once
#ifndef SRC_MENUSTATE_H_
#define SRC_MENUSTATE_H_
#include "SDL.h"
#include "SDL_image.h"
#include <vector>
#include "Game.h"
#include "Button.h"


class MenuState : public State {
public:
	MenuState(GameDataRef data);

	bool Init();

	void HandleInput();
	void Update(float dt);
	void Draw();
	void HandleClick(int x, int y);

private:
	GameDataRef data;
	SDL_Texture *_background;
	SDL_Rect src, dest;
	std::vector<class Button*> buttons;
};

#endif /* SRC_MENUSTATE_H_ */