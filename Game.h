#pragma once
#ifndef SRC_GAME_H_
#define SRC_GAME_H_
#include <memory>
#include <string>
#include "SDL.h"
#include "SDL_image.h"
#include "StateMachine.h"

struct GameData {
	StateMachine machine;
	SDL_Renderer *renderer;
	SDL_Window *window;
	SDL_Surface *surface;
	SDL_Rect camera;
};

typedef std::shared_ptr<GameData> GameDataRef;

class Game {

public:
	Game(int width, int height, const char* title);

	static bool running;
	
private:
	
	
	GameDataRef _data = std::make_shared<GameData>();

	void Run();
};
#endif /* SRC_GAME_H_ */