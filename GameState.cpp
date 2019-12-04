
#include "GameState.h"
#include "Button.h"
#include "PauseState.h"
#include "MapState.h"
#include <fstream>



GameState::GameState(GameDataRef data, std::string level) : data(data) {
	this->level = level;
	printf("Level:%s\n", this->level.c_str());
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
	data->audioManager.LoadMusic("Assets/" + level + "/backgroundMusic.mp3", "backgroundMusic");
	//sounds
	data->audioManager.LoadChunk("Assets/CoinSound.wav", "coinSound");
	data->audioManager.LoadChunk("Assets/Jump.wav", "jumpSound");
	data->audioManager.LoadChunk("Assets/BowSound.wav", "bowSound");
	//game textures
	data->texmanager.LoadTexture("Assets/tileset.png", "tileset", data->renderer);
	data->texmanager.LoadTexture("Assets/water.bmp", "hitbox", data->renderer);
	data->texmanager.LoadTexture("Assets/Arrow.png", "arrow", data->renderer);
	data->texmanager.LoadTexture("Assets/armandbow.png", "armandbow", data->renderer);
	data->texmanager.LoadTexture("Assets/Bird.png", "bird", data->renderer);
	data->texmanager.LoadTexture("Assets/Knight.png", "knight", data->renderer);
	data->texmanager.LoadTexture("Assets/Numbers.png", "numbers", data->renderer);
	data->texmanager.LoadTexture("Assets/craigwithbow.png", "player", data->renderer);
	data->texmanager.LoadTexture("Assets/Coin.png", "coin", data->renderer);
	data->texmanager.LoadTexture("Assets/key.png", "key", data->renderer);
	data->texmanager.LoadTexture("Assets/PauseButton.png", "pause button", data->renderer);
	//pause textures
	data->texmanager.LoadTexture("Assets/ResumeButton.png", "resume button", data->renderer);
	data->texmanager.LoadTexture("Assets/BackButton.png", "back button", data->renderer);
	

	printf("Textures loaded\n");

	//initialize map
	map = new Map(data);
	std::ifstream inFile;
	inFile.open("Assets/" + level + "/Collidables.txt");
	if (!inFile) {
		printf("Unable to open file Collidables.txt");
		exit(1);   // call system to stop
	}
	inFile >> levelWidth;
	inFile >> levelHeight;

	//load level
	printf("Loading level...\n");
	map->LoadCollidables("Assets/" + level + "/Collidables.txt");
	map->LoadBackground("Assets/" + level + "/Collidables.txt", "Assets/" + level + "/Background.png");
	map->LoadCoins("Assets/" + level + "/Others.txt");

	//initialize entities
	//initialize player
	loadCharacters("Assets/" + level + "/Characters.txt");
	
	player->loadtexture("player", 0, 0);
	player->loadHitboxTexture("hitbox", 0, 0);

	pauseButton = new Button(data, .9*SCREEN_WIDTH, SCREEN_HEIGHT*.1, 32, 32, 75, 75);
	pauseButton->loadtexture("pause button", 0, 0);
	
	backgroundMusic = data->audioManager.GetMusic("backgroundMusic");
	printf("Level loaded\n");

	Mix_PlayMusic(backgroundMusic, -1);
	playing = true;
	paused = false;
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
				break;
		}
		keystate = SDL_GetKeyboardState(NULL);
		player->handleinput(event, keystate);
		

	}
}


void GameState::Update(float dt) {

	player->update(map->getCollidables(), dt);

	for (auto&& enemy : enemies) {
		enemy->update(map->getCollidables(), dt, player);
	}
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

	this->data->camera.x = (int)(player->position->x - SCREEN_WIDTH/2);
	this->data->camera.y = (int)(player->position->y - SCREEN_HEIGHT/2);
	if (this->data->camera.x < 0) {
		this->data->camera.x = 0;
	}
	if (this->data->camera.y < 0) {
		this->data->camera.y = 0;
	}
	if (this->data->camera.x + this->data->camera.w > levelWidth* BLOCK_SIZE) {
		this->data->camera.x = levelWidth* BLOCK_SIZE - this->data->camera.w;
	}
	if (this->data->camera.y + this->data->camera.h > levelHeight* BLOCK_SIZE) {
		this->data->camera.y = levelHeight* BLOCK_SIZE - this->data->camera.h;
	}

	SDL_RenderClear(this->data->renderer);
	map->DrawMap();
	player->draw();
	for (auto&& enemy : enemies) {
		enemy->draw();
	}
	pauseButton->draw();
	if (!paused) {
		SDL_RenderPresent(data->renderer);
	}
	
}



void GameState::HandleClick(int x, int y) {
	if (x > pauseButton->dest.x&& x < pauseButton->dest.x + pauseButton->dest.w && y > pauseButton->dest.y&& y < pauseButton->dest.y + pauseButton->dest.h) {
		pauseButton->handleClick();
		paused = true;
		data->machine.AddState(StateRef(new PauseState(data, this)), false);
		SDL_Delay(100);
	}
}

void GameState::loadCharacters(std::string path) {
	int mapWidth, mapHeight;
	std::ifstream inFile;
	inFile.open(path);
	if (!inFile) {
		printf("Unable to open file %s", path.c_str());
		exit(1);   // call system to stop
	}
	inFile >> mapWidth;
	inFile >> mapHeight;
	int type = 0;
	int layer;
	Enemy* ent;
	for (int row = 0; row < mapHeight; row++) {
		for (int col = 0; col < mapWidth; col++) {
			inFile >> type;
			//printf("%d", type);
			switch (type) {
			case -1:
				break;
			case 35:
				player = new Player(col * BLOCK_SIZE, row * BLOCK_SIZE, 100, 100, 3, 100, data);
				data->camera.x = col * BLOCK_SIZE - SCREEN_WIDTH / 2;
				data->camera.y = row * BLOCK_SIZE - SCREEN_HEIGHT/2;
				break;
			case 23:
				ent = new Bird(col * BLOCK_SIZE, row * BLOCK_SIZE, 150, 150, 2, 100, data);
				enemies.push_back(ent);
				break;
			case 39:
				ent = new Knight (col * BLOCK_SIZE, row * BLOCK_SIZE-100, 200, 200, 3, 100, data);
				enemies.push_back(ent);
				break;
			default:
				break;
			}
		}
	}
}


void GameState::clean() {
	
}

void GameState::Resume() {
	if (!playing) {
		data->machine.RemoveState();
		data->machine.AddState(StateRef(new MapState(data)));
	}
	paused = false;
	pauseButton->src.x = 0;
}