#pragma once
#ifndef SRC_PAUSESTATE_H_
#define SRC_PAUSESTATE_H_
#include "SDL.h"
#include "SDL_image.h"
#include <vector>
#include "Game.h"
#include "GameState.h"
#include "Button.h"


class PauseState : public State {
public:
	PauseState(GameDataRef data, GameState* game);
	~PauseState();

	void Identify() { printf("Pause State"); }
	bool Init();

	void HandleInput();
	void Update();
	void Draw();
	void HandleClick(int x, int y);

private:
	GameDataRef data;
	GameState* game;
	SDL_Rect src, dest;
	Button* resumeButton;
	Button* backButton;
	std::vector<class Button*> buttons;
};

#endif /* SRC_PAUSESTATE_H_ */