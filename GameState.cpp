
#include "GameState.h"
#include "Button.h"
#include "PauseState.h"
#include "MapState.h"
#include <fstream>



GameState::GameState(GameDataRef data, const char* Level) : data(data){

}

GameState::~GameState() {
	printf("Deleting game state");
	delete map;
	delete player;
	for (auto enemy : enemies) {
		delete enemy;
	}
	delete pauseButton;
	data->texmanager.DestroyTextures();
	data->audioManager.DestroyChunks();
	data->audioManager.DestroyMusic();

}


bool GameState::Init() {
	printf("Loading Game assets...\n");
	//background music
	data->audioManager.LoadMusic("Images/Song2.mp3", "backgroundLevel1");
	//sounds
	data->audioManager.LoadChunk("Images/CoinSound.wav", "coinSound");
	data->audioManager.LoadChunk("Images/Jump.wav", "jumpSound");
	data->audioManager.LoadChunk("Images/BowSound.wav", "bowSound");
	//game textures
	data->texmanager.LoadTexture("Images/water.bmp", "hitbox", data->renderer);
	data->texmanager.LoadTexture("Images/Arrow.png", "arrow", data->renderer);
	data->texmanager.LoadTexture("Images/armandbow.png", "armandbow", data->renderer);
	data->texmanager.LoadTexture("Images/Bird.png", "bird", data->renderer);
	data->texmanager.LoadTexture("Images/Knight.png", "knight", data->renderer);
	data->texmanager.LoadTexture("Images/Numbers.png", "numbers", data->renderer);
	data->texmanager.LoadTexture("Images/craigwithbow.png", "player", data->renderer);
	data->texmanager.LoadTexture("Images/Coin.png", "coin", data->renderer);
	data->texmanager.LoadTexture("Images/key.png", "key", data->renderer);
	data->texmanager.LoadTexture("Images/PauseButton.png", "pause button", data->renderer);
	//pause textures
	data->texmanager.LoadTexture("Images/ResumeButton.png", "resume button", data->renderer);
	data->texmanager.LoadTexture("Images/BackButton.png", "back button", data->renderer);
	

	printf("Textures loaded\n");

	//initialize map
	map = new Map(data);

	//load level
	printf("Loading level...\n");

	map->LoadCollidables("Images/collidables.txt");
	map->LoadBackground("Images/background.txt");
	map->LoadCoins("Images/others.txt");

	//initialize entities
	//initialize player
	player = new Player(50, 200, 75, 75, 3, 100, data);
	player->loadtexture("player", 0, 0);
	player->loadHitboxTexture("hitbox", 0, 0);
	//initialize birds
	for (int i = 0; i < 20; i++) {
		bird = new Bird(4200, 800, 75, 75, 2, 100, data);
		enemies.push_back(bird);

	}
	//initialize knight
	knight = new Knight(4700, 800, 150, 150, 2, 100, data);
	enemies.push_back(knight);

	pauseButton = new Button(data, SCREEN_WIDTH - 100, SCREEN_HEIGHT*.05, 32, 32, 50, 50);
	pauseButton->loadtexture("pause button", 0, 0);
	
	backgroundMusic = data->audioManager.GetMusic("backgroundLevel1");
	printf("Level loaded\n");

	Mix_PlayMusic(backgroundMusic, -1);
	playing = true;
	return true;
}

void GameState::HandleInput() {
	
	SDL_Event event;
	//Handle events on queue
	int mouseX, mouseY;
	while (SDL_PollEvent(&event) != 0)
	{
		//User requests quit
		switch (event.type) {
			case SDL_QUIT:
				Game::running = false;
				break;
			case SDL_MOUSEBUTTONDOWN:
				SDL_GetMouseState(&mouseX, &mouseY);
				HandleClick(mouseX, mouseY);
				break;
			default:
				//User presses a key
				
				break;
		}
		keystate = SDL_GetKeyboardState(NULL);
		player->handleinput(event, keystate);
		

	}
}


void GameState::Update(float dt) {

	player->update(map->getCollidables(), enemies, dt);

	for (auto&& enemy : enemies) {
		enemy->update(map->getCollidables(), dt);
	}
	knight->update(map->getCollidables(), dt, player);
	map->UpdateMap(dt);


	int mouseX, mouseY;
	SDL_GetMouseState(&mouseX, &mouseY);
	pauseButton->update();
	if (mouseX > pauseButton->dest.x&& mouseX < pauseButton->dest.x + pauseButton->dest.w && mouseY > pauseButton->dest.y&& mouseY < pauseButton->dest.y + pauseButton->dest.h) {
		pauseButton->hovering = true;
	}
	else {
		pauseButton->hovering = false;
	}
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
	player->draw();
	for (auto&& enemy : enemies) {
		enemy->draw();
	}

	pauseButton->draw();
	SDL_RenderPresent(data->renderer);
}



void GameState::HandleClick(int x, int y) {
	if (x > pauseButton->dest.x&& x < pauseButton->dest.x + pauseButton->dest.w && y > pauseButton->dest.y&& y < pauseButton->dest.y + pauseButton->dest.h) {
		pauseButton->handleClick();

		data->machine.AddState(StateRef(new PauseState(data, this)), false);
		SDL_Delay(100);
	}
}


void GameState::clean() {
	
}

void GameState::Resume() {
	if (!playing) {
		data->machine.RemoveState();
		data->machine.AddState(StateRef(new MapState(data)));
	}
	pauseButton->src.x = 0;
}