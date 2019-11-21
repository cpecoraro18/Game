#include "PauseState.h"
#include "GameState.h"
#include "MapState.h"
#include "DEFINITIONS.h"

PauseState::PauseState(GameDataRef data, GameState* pausedGame) : data(data) {
	game = pausedGame;
}

PauseState::~PauseState() {
	printf("Deleting pause state");
	for (auto button : buttons) {
		delete button;
	}
}

bool PauseState::Init() {
	
	resumeButton = new Button(data, SCREEN_WIDTH / 2 - BUTTON_WIDTH/2, SCREEN_HEIGHT / 3 , 
		BUTTON_SPRITE_WIDTH, BUTTON_SPRITE_HEIGHT, BUTTON_WIDTH, BUTTON_HEIGHT);
	resumeButton->loadtexture("resume button", 0, 0);
	buttons.push_back(resumeButton);
	backButton = new Button(data, SCREEN_WIDTH / 2 - BUTTON_WIDTH/2, SCREEN_HEIGHT / 2,
		BUTTON_SPRITE_WIDTH, BUTTON_SPRITE_HEIGHT, BUTTON_WIDTH, BUTTON_HEIGHT);
	backButton->loadtexture("back button", 0, 0);
	buttons.push_back(backButton);

	return true;
}

void PauseState::HandleInput() {

	SDL_Event event;
	int mouseX, mouseY;
	//Handle events on queue
	while (SDL_PollEvent(&event) != 0)
	{
		switch (event.type) {
		case SDL_QUIT:
			Game::running = false;
			break;
		case SDL_MOUSEBUTTONDOWN:
			SDL_GetMouseState(&mouseX, &mouseY);
			HandleClick(mouseX, mouseY);
			break;
		case SDL_KEYDOWN:
			//Select surfaces based on key press
			switch (event.key.keysym.sym)
			{

			default:
				
				break;
			}
		}
	}

}

void PauseState::HandleClick(int x, int y) {
	if (x > resumeButton->dest.x&& x < resumeButton->dest.x + resumeButton->dest.w && y > resumeButton->dest.y&& y < resumeButton->dest.y + resumeButton->dest.h) {
		resumeButton->handleClick();

		data->machine.RemoveState();
		SDL_Delay(100);
	}
	if (x > backButton->dest.x&& x < backButton->dest.x + backButton->dest.w && y > backButton->dest.y&& y < backButton->dest.y + backButton->dest.h) {
		backButton->handleClick();
		game->playing = false;
		data->machine.RemoveState();
		SDL_Delay(100);
	}
}

void PauseState::Update(float dt) {
	int mouseX, mouseY;
	SDL_GetMouseState(&mouseX, &mouseY);
	for (auto button : buttons) {
		button->update();
		if (mouseX > button->dest.x&& mouseX < button->dest.x + button->dest.w && mouseY > button->dest.y&& mouseY < button->dest.y + button->dest.h) {
			button->hovering = true;
		}
		else {
			button->hovering = false;
		}
	}

}
void PauseState::Draw() {
	SDL_RenderClear(this->data->renderer);
	game->Draw();
	for (auto button : buttons) {
		button->draw();
	}
	
	SDL_RenderPresent(data->renderer);
}