#pragma once
#ifndef SRC_MAPSTATE_H_
#define SRC_MAPSTATE_H_
#include "SDL.h"
#include "SDL_image.h"
#include "Game.h"
#include "Button.h"
#include <vector>


class MapState : public State {
public:
	MapState(GameDataRef data);

	bool Init();

	void HandleInput();
	void Update(float dt);
	void Draw();
	void HandleClick(int x, int y);

private:
	GameDataRef data;
	SDL_Texture* map;
	SDL_Rect src, dest;

	std::vector<class Button*> levels;

	Button* backButton;
};

#endif /* SRC_MAPSTATE_H_ */
