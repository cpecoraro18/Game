#include "Game.h"
#include "GameState.h"
#include "Player.h"
#include <fstream>

GameState::GameState(GameDataRef data) : data(data){

}


bool GameState::Init() {
	data->texmanager.LoadTexture("Images/water.bmp", "hitbox", data->renderer);
	//initialize map
	map = new Map(data);
	//load level
	map->LoadCollidables("Images/collidables.txt");
	map->LoadBackground("Images/background.txt");
	map->LoadCoins("Images/others.txt");
	//initialize player
	player = new Player(50, 200, 75, 75, 3, 100, data);
	characters.push_back(player);
	player->loadtexture("Images/craig.png", "player", 0, 0);
	player->loadHitboxTexture("hitbox", 0, 0);
	return true;
}

void GameState::HandleInput() {
	
	SDL_Event event;
	//Handle events on queue
	while (SDL_PollEvent(&event) != 0)
	{
		
		//User requests quit
		if (event.type == SDL_QUIT)
		{
			Game::running = false;
		}
		//User presses a key
		player->handleinput(event);

	}
}


void GameState::Update(float dt) {
	player->update(map->getCollidables(), dt);
	map->UpdateMap(dt);

}

void GameState::Draw() {


	this->data->camera.x = player->position->x - 400;
	this->data->camera.y = (player->position->y - 320)/1.25;
	if (this->data->camera.x < 0) {
		this->data->camera.x = 0;
	}
	if (this->data->camera.y < 0) {
		this->data->camera.y = 0;
	}
	if (this->data->camera.x + this->data->camera.w > 5500) {
		this->data->camera.x = 5500 - this->data->camera.w;
	}
	if (this->data->camera.y + this->data->camera.h > 1650) {
		this->data->camera.y = 1650 - this->data->camera.h;
	}
	SDL_RenderClear(this->data->renderer);
	map->DrawMap();
	for (auto&& ent : characters) {
		ent->draw();
	}
	SDL_RenderPresent(data->renderer);
}

void GameState::clean() {
	
}