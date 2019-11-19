#include "MenuState.h"
#include "GameState.h"
#include "MapState.h"
#include "DEFINITIONS.h"

MenuState::MenuState(GameDataRef data) : data(data){

}

bool MenuState::Init() {
	printf("Loading Menu textures...\n");
	data->texmanager.LoadTexture("Images/MenuBackground.png", "menu background", data->renderer);
	printf("Textures loaded\n");
	_background = data->texmanager.GetTexture("menu background");
	src.x = 0;
	src.y = 0;
	src.h = 640;
	src.w = 832;
	dest.x = 0;
	dest.y = 0;
	dest.h = SCREEN_HEIGHT;
	dest.w = SCREEN_WIDTH;
	Button* startButton = new Button(data, 350, 250, 200, 200);
	startButton->loadtexture("Images/PlayButton.png", "play button", 0, 0);
	buttons.push_back(startButton);

	return true;
}

void MenuState::HandleInput() {

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

			case SDLK_RETURN:
				data->machine.AddState(StateRef(new MapState(data)));
				break;
			}
		}
	}

}

void MenuState::HandleClick(int x, int y) {
	for (auto button : buttons) {
		if (x > button->dest.x && x < button->dest.x + button->dest.w && y > button->dest.y && y < button->dest.y + button->dest.h) {
			button->handleClick();
			
			data->machine.AddState(StateRef(new MapState(data)));
			SDL_Delay(100);
		}
	}
}
void MenuState::Update(float dt) {
	int mouseX, mouseY;
	SDL_GetMouseState(&mouseX, &mouseY);
	for (auto button : buttons) {
		button->update();
		if (mouseX > button->dest.x && mouseX < button->dest.x + button->dest.w && mouseY > button->dest.y && mouseY < button->dest.y + button->dest.h) {
			button->hovering = true;
		}
		else {
			button->hovering = false;
		}
	}
	
}
void MenuState::Draw() {
	SDL_RenderClear(this->data->renderer);
	data->texmanager.Draw(_background, src, dest, data->renderer);
	for (auto button : buttons) {
		button->draw();
	}
	SDL_RenderPresent(data->renderer);
}