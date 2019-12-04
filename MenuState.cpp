#include "MenuState.h"
#include "GameState.h"
#include "MapState.h"
#include "DEFINITIONS.h"

MenuState::MenuState(GameDataRef data) : data(data){

}

MenuState::~MenuState() {
	printf("Deleting menu state");
	for (auto button : buttons) {
		delete button;
	}
	data->texmanager.DestroyTextures();
	data->audioManager.DestroyChunks();
	data->audioManager.DestroyMusic();

}

bool MenuState::Init() {
	printf("Loading Menu textures...\n");
	data->texmanager.LoadTexture("Assets/MenuBackground.png", "menu background", data->renderer);
	data->texmanager.LoadTexture("Assets/PlayButton.png", "play button", data->renderer);
	data->texmanager.LoadTexture("Assets/Quit.png", "quit button", data->renderer);
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
	startButton = new Button(data, SCREEN_WIDTH/2 - BUTTON_WIDTH/2, SCREEN_HEIGHT/2-BUTTON_HEIGHT/2, 
		BUTTON_SPRITE_WIDTH, BUTTON_SPRITE_HEIGHT, BUTTON_WIDTH, BUTTON_HEIGHT);
	startButton->loadtexture( "play button", 0, 0);
	buttons.push_back(startButton);
	quitButton = new Button(data, SCREEN_WIDTH / 2 - BUTTON_WIDTH / 2, 2*SCREEN_HEIGHT / 3- BUTTON_HEIGHT / 2,
		BUTTON_SPRITE_WIDTH, BUTTON_SPRITE_HEIGHT, BUTTON_WIDTH, BUTTON_HEIGHT);
	quitButton->loadtexture("quit button", 0, 0);
	buttons.push_back(quitButton);

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
	if (x > startButton->dest.x && x < startButton->dest.x + startButton->dest.w && y > startButton->dest.y && y < startButton->dest.y + startButton->dest.h) {
		startButton->handleClick();
			
		data->machine.AddState(StateRef(new MapState(data)));
		SDL_Delay(100);
	}
	if (x > quitButton->dest.x&& x < quitButton->dest.x + quitButton->dest.w && y > quitButton->dest.y&& y < quitButton->dest.y + quitButton->dest.h) {
		quitButton->handleClick();

		Game::running = false;
		SDL_Delay(100);
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