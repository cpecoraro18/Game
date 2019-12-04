#include "Game.h"
#include "SplashState.h"
#include "GameState.h"
#include "MapState.h"
#include "State.h"
#include <algorithm>
#include <time.h>


bool Game::running = true;

Game::Game(int width, int height, const char* title) {

	fps = 0;
	frameTime = 0;

	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
		
		("SDL could not initialize SDL_Error: %s\n", SDL_GetError());
		return;
	}
	else {
		printf("SDL Initialized\n");
		//create window
		_data->window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
		if (_data->window == NULL) {
			printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
			return;
		}
		else {
			printf("Window created\n");
			//create renderer
			_data->renderer = SDL_CreateRenderer(_data->window, -1, 0);
			if (_data->renderer == NULL) {
				printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
				return;
			}
			//get window surface
			printf("Renderer Created\n");
			_data->surface = SDL_GetWindowSurface(_data->window);
			_data->camera = { 0, 0, width, height };
		}
	}
	//add states
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
		printf("Audio could not be created! Mix_Error: %s\n", Mix_GetError());
		return; 
	}
	else {
		printf("Initialized Audio");
	}
	_data->machine.AddState(StateRef(new SplashState(_data)));
	this->Run();
}

void Game::Run() {
	
	float frameStart, frameEnd, deltaTime;
	frameStart = 0;
	frameEnd = 0;
	deltaTime = 0;
	float timeCounter = 0;
	
	while (running) {
	
		if (deltaTime < 1) {
			frameStart = SDL_GetTicks();
			SDL_Delay(1);
			frameEnd = SDL_GetTicks();
			deltaTime = (frameEnd - frameStart);
		}
		timeCounter += deltaTime;

		frameStart = SDL_GetTicks();
		_data->machine.ProcessStateChanges();
		_data->machine.GetActiveState()->HandleInput();
		_data->machine.GetActiveState()->Update(deltaTime/100.0f);
		CalculateFPS();
		frameEnd = SDL_GetTicks();
		deltaTime = (frameEnd - frameStart);

		_data->machine.GetActiveState()->Draw();
		

		//print frame rate
		static int frameCounter = 0;
		frameCounter++;
		if (frameCounter == 60) {
			printf("FPS: %f\n", fps);
			timeCounter = 0;
			frameCounter = 0;
		}

		//limit frame rate
		if (1000.0f / maxFPS > deltaTime) {
			SDL_Delay(1000.0f/maxFPS - deltaTime);
		}
		
		
		
	}
	
	//Destroy window
	SDL_DestroyWindow(_data->window);
	_data->window = NULL;
	//destroy renderer
	SDL_DestroyRenderer(_data->renderer);

	//Quit SDL subsystems
	SDL_Quit();

}

void Game::CalculateFPS() {
	static const int NUM_SAMPLES = 100;
	static float frameTimes[NUM_SAMPLES];
	static int currentFrame = 0;

	static float prevTicks = SDL_GetTicks();
	float currentTicks;
	currentTicks = SDL_GetTicks();

	frameTime = currentTicks - prevTicks;
	frameTimes[currentFrame%NUM_SAMPLES] = frameTime;

	prevTicks = currentTicks;
	int count;
	currentFrame++;
	if (currentFrame < NUM_SAMPLES) {
		count = currentFrame;
	}
	else {
		count = NUM_SAMPLES;
	}

	float frameTimeAverage = 0;

	for (int i = 0; i < count; i++) {
		frameTimeAverage += frameTimes[i];
	}
	frameTimeAverage /= count;

	if (frameTimeAverage > 0) {
		fps = 1000.0f / frameTimeAverage;
	}

	else {
		fps = 61.0f;
	}
	
	

}