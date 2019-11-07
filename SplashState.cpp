#include "SplashState.h"
#include "TextureManager.h"
#include "GameState.h"
#include "DEFINITIONS.h"

SplashState::SplashState(GameDataRef data) : data(data){

}

bool SplashState::Init() {
	_background = TextureManager::LoadTexture("Images/SplashScreen.png", data);
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
				data->machine.AddState(StateRef(new GameState(data)));
				break;
			}
		}
	}
}
void SplashState::Update(float dt) {

}
void SplashState::Draw() {
	SDL_RenderClear(this->data->renderer);
	TextureManager::Draw(_background, src, dest, data);
	SDL_RenderPresent(data->renderer);
}