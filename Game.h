#pragma once
#ifndef SRC_GAME_H_
#define SRC_GAME_H_
#include <memory>
#include <string>
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_mixer.h"
#include "StateMachine.h"
#include "TextureManager.h"

struct GameData {
	StateMachine machine;
	TextureManager texmanager;
	SDL_Renderer *renderer;
	SDL_Window *window;
	SDL_Surface *surface;
	SDL_Rect camera;
};

typedef std::shared_ptr<GameData> GameDataRef;

class Game {

public:
	Game(int width, int height, const char* title);

	void Run();

	void CalculateFPS();
	static bool running;
	
private:
	float fps;
	float frameTime;
	float maxFPS = 60;

	
	
	GameDataRef _data = std::make_shared<GameData>();

	
};
#endif /* SRC_GAME_H_ */