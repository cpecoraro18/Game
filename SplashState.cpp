#include "SplashState.h"
#include "TextureManager.h"
#include <time.h>
#include "GameState.h"
#include "MenuState.h"
#include "DEFINITIONS.h"

SplashState::SplashState(GameDataRef data) : data(data){

}

SplashState::~SplashState() {
	printf("Deleting splash state");
	data->texmanager.DestroyTextures();
	data->audioManager.DestroyChunks();
	data->audioManager.DestroyMusic();
}

bool SplashState::Init() {
	data->texmanager.LoadTexture("Images/SplashScreen.png", "splash background", data->renderer);
	_background = data->texmanager.GetTexture("splash background");
	src.x = 0;
	src.y = 0;
	src.h = 32;
	src.w = 32;
	dest.x = 0;
	dest.y = 0;
	dest.h = SCREEN_HEIGHT;
	dest.w = SCREEN_WIDTH;
	return true;
}

void SplashState::HandleInput() {
	SDL_Event event;
	//Handle events on queue
	while (SDL_PollEvent(&event) != 0)
	{

		//User requests quit
		if (event.type == SDL_QUIT)
		{
			Game::running = false;
		}
		if (event.type == SDL_KEYDOWN)
		{
			//Select surfaces based on key press
			switch (event.key.keysym.sym)
			{

			case SDLK_RETURN:
				data->machine.AddState(StateRef(new MenuState(data)));
				break;
			}
		}
	}
}
void SplashState::Update(float dt) {
	count++;
	if (count > 120) {
		data->machine.AddState(StateRef(new MenuState(data)));
	}
	
}
void SplashState::Draw() {
	SDL_RenderClear(this->data->renderer);
	data->texmanager.Draw(_background, src, dest, data->renderer);
	SDL_RenderPresent(data->renderer);
}