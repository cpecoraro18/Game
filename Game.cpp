#include "Game.h"
#include "SplashState.h"
#include "State.h"
#include <algorithm>


bool Game::running = true;

Game::Game(int width, int height, const char* title) {


	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
		printf("SDL could not initialize SDL_Error: %s\n", SDL_GetError());
		return;
	}
	else {
		//create window
		_data->window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
			width, height, 0);
		if (_data->window == NULL) {
			printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
			return;
		}
		else {
			//create renderer
			_data->renderer = SDL_CreateRenderer(_data->window, -1, 0);
			if (_data->renderer == NULL) {
				printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
				return;
			}
			//get window surface
			_data->surface = SDL_GetWindowSurface(_data->window);
			_data->camera = { 0, 0, width, height };
		}
	}
	//add states
	_data->machine.AddState(StateRef(new SplashState(_data)));
	this->Run();
}

void Game::Run() {
	
	float frameStart, frameEnd, deltaTime;
	frameStart = 0;
	frameEnd = 0;
	deltaTime = 0;
	
	while (running) {
		if (deltaTime < 1) {
			frameStart = SDL_GetTicks();
			SDL_Delay(1);
			frameEnd = SDL_GetTicks();
			deltaTime = frameEnd - frameStart;
		}

		frameStart = SDL_GetTicks();
		_data->machine.ProcessStateChanges();
		_data->machine.GetActiveState()->HandleInput();
		_data->machine.GetActiveState()->Update(deltaTime/1000);
		frameEnd = SDL_GetTicks();
		deltaTime = frameEnd - frameStart;
		
		_data->machine.GetActiveState()->Draw();
		
	}
	
	//Destroy window
	SDL_DestroyWindow(_data->window);
	_data->window = NULL;
	//destroy renderer
	SDL_DestroyRenderer(_data->renderer);

	//Quit SDL subsystems
	SDL_Quit();

}