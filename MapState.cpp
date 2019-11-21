#include "MapState.h"
#include "MenuState.h"
#include "TextureManager.h"
#include <time.h>
#include "GameState.h"
#include "DEFINITIONS.h"

MapState::MapState(GameDataRef data) : data(data) {
}

MapState::~MapState() {
	printf("Deleting map state");
	for (auto level : levels) {
		delete level;
	}
	delete backButton;
	data->texmanager.DestroyTextures();
	data->audioManager.DestroyChunks();
	data->audioManager.DestroyMusic();
}
bool MapState::Init() {
	data->texmanager.LoadTexture("Images/Location.png", "location", data->renderer);
	data->texmanager.LoadTexture("Images/Map2.png", "map", data->renderer);
	data->texmanager.LoadTexture("Images/BackButton.png", "back button", data->renderer);
	map = data->texmanager.GetTexture("map");
	src.x = 0;
	src.y = 0;
	src.h = 160;
	src.w = 320;
	dest.x = 0;
	dest.y = 0;
	dest.h = SCREEN_HEIGHT;
	dest.w = SCREEN_WIDTH;

	Button* level1Button = new Button(data, SCREEN_WIDTH/6, SCREEN_HEIGHT/2, 32, 32, 32, 32);
	level1Button->loadtexture( "location", 0, 0);
	levels.push_back(level1Button);

	backButton = new Button(data, 50, 50, 64, 32, 100, 50);
	backButton->loadtexture("back button", 0, 0);
	return true;
}

void MapState::HandleInput() {
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
				break;
			}
		}
	}
}
void MapState::Update(float dt) {
	int mouseX, mouseY;
	SDL_GetMouseState(&mouseX, &mouseY);
	for (auto level : levels) {
		level->update();
		if (mouseX > level->dest.x&& mouseX < level->dest.x + level->dest.w && mouseY > level->dest.y&& mouseY < level->dest.y + level->dest.h) {
			level->hovering = true;
		}
		else {
			level->hovering = false;
		}
	}
	backButton->update();
	if (mouseX > backButton->dest.x&& mouseX < backButton->dest.x + backButton->dest.w && mouseY > backButton->dest.y&& mouseY < backButton->dest.y + backButton->dest.h) {
		backButton->hovering = true;
	}
	else {
		backButton->hovering = false;
	}
}
void MapState::Draw() {
	SDL_RenderClear(this->data->renderer);
	data->texmanager.Draw(map, src, dest, data->renderer);
	for (auto level : levels) {
		level->draw();
	}
	backButton->draw();
	SDL_RenderPresent(data->renderer);
}

void MapState::HandleClick(int x, int y) {
	for (auto level : levels) {
		if (x > level->dest.x && x < level->dest.x + level->dest.w && y > level->dest.y && y < level->dest.y + level->dest.h) {
			level->handleClick();

			data->machine.AddState(StateRef(new GameState(data, "")));
			SDL_Delay(100);
		}
	}
	if (x > backButton->dest.x&& x < backButton->dest.x + backButton->dest.w && y > backButton->dest.y&& y < backButton->dest.y + backButton->dest.h) {
		backButton->handleClick();

		data->machine.AddState(StateRef(new MenuState(data)));
		SDL_Delay(100);
	}
}