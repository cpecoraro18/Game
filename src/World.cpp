#include "World.h"
#include "TextureManager.h"
#include "Coin.h"
#include "Entity.h"
#include "Player.h"
#include "Key.h"
#include "Spike.h"
#include "Knight.h"
#include "Bird.h"
#include "EndLevel.h"
#include <iostream>
#include <fstream>


World::World(GameDataRef data): data(data) {
	src.x = 0;
	src.y = 0;
	dest.x = 0;
	dest.y = 0;

}

World::~World() {
	printf("Deleting World\n");
	for (auto block : collidables) {
		delete block;
	}
	for (auto enemy : enemies) {
		delete enemy;
	}
	delete player;

}

void World::LoadCollidables(std::string path) {
	std::ifstream inFile;
	int mapColumns, mapRows;
	inFile.open(path);
	if (!inFile) {
		printf("Unable to open file %s", path.c_str());
		exit(1);   // call system to stop
	}
	inFile >> mapColumns;
	inFile >> mapRows;
	worldWidth = mapColumns * BLOCK_SIZE;
	worldHeight = mapRows * BLOCK_SIZE;
	collidables.reserve(mapRows*mapColumns);
	int type = 0;
	int layer;
	for (int row = 0; row < mapRows; row++) {
		for (int col = 0; col < mapColumns; col++) {
			inFile >> type;
			//printf("%d", type);
			Block* block;
			switch (type) {
			case -1:
				break;
			default:

				block = new Block(data, col * BLOCK_SIZE, row * BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE);
				layer = type / 4;
				block->loadtexture("tileset", type%4*32, layer*32);
				block->loadHitboxTexture("hitbox", 0, 0);
				collidables.push_back(block);
				break;
			}
		}
	}
}

void World::LoadBackground(std::string background) {


	dest.w = worldWidth;
	dest.h = worldHeight;
	src.w = worldWidth;
	src.h = worldHeight;
	data->texmanager.LoadTexture(background,"background", data->renderer);
	this->background = data->texmanager.GetTexture("background");

}

void World::LoadCoins(std::string path) {
	std::ifstream inFile;
	int mapColumns, mapRows;
	inFile.open(path);
	if (!inFile) {
		printf("Unable to open file datafile.txt");
		exit(1);   // call system to stop
	}
	inFile >> mapColumns;
	inFile >> mapRows;

	int type = 0;
	int layer;
	for (int row = 0; row < mapRows; row++) {
		for (int col = 0; col < mapColumns; col++) {
			inFile >> type;
			layer = type / 4;
			Entity* ent;
			switch (type) {
			case -1:
				break;
			case 16:
				ent = new Coin(data, col * BLOCK_SIZE + BLOCK_SIZE/6, row * BLOCK_SIZE + BLOCK_SIZE/6, 2*BLOCK_SIZE/3, 2*BLOCK_SIZE/3, 5, 100);
				ent->loadtexture("coin", 0, 0);
				collidables.push_back(ent);
				break;
			case 19:
				ent = new Spike(data, col * BLOCK_SIZE, row * BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE, false);
				ent->loadtexture("tileset", type % 8 * 32, layer * 32);
				collidables.push_back(ent);
				break;
			case 18:
				ent = new Spike(data, col * BLOCK_SIZE, row * BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE, true);
				ent->loadtexture("tileset", type % 8 * 32, layer * 32);
				collidables.push_back(ent);
				break;
			case 17:
				ent = new Key(data, col * BLOCK_SIZE, row * BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE, 4, 100);
				ent->loadtexture("key", 0, 0);
				collidables.push_back(ent);
				break;
			case 20:
				ent = new Block(data, col * BLOCK_SIZE, row * BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE);
				ent->loadtexture("tileset", type % 4 * 32, layer * 32);
				collidables.push_back(ent);
				break;
			case 50:
				ent = new EndLevel(data, col * BLOCK_SIZE, row * BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE);
				ent->loadtexture("tileset", type % 4 * 32, layer * 32);
				collidables.push_back(ent);
				break;
			default:
				break;
			}
		}
	}

}

void World::LoadCharacters(std::string path) {
	std::ifstream inFile;
	int mapColumns, mapRows;
	inFile.open(path);
	if (!inFile) {
		printf("Unable to open file %s", path.c_str());
		exit(1);   // call system to stop
	}
	inFile >> mapColumns;
	inFile >> mapRows;
	int type = 0;
	int layer;
	Enemy* ent;
	for (int row = 0; row < mapRows; row++) {
		for (int col = 0; col < mapColumns; col++) {
			inFile >> type;
			//printf("%d", type);
			switch (type) {
			case -1:
				break;
			case 35:
				player = new Player(col * BLOCK_SIZE, row * BLOCK_SIZE, 100, 100, 3, 100, data);
				player->loadtexture("player", 0, 0);
				data->camera.x = col * BLOCK_SIZE - SCREEN_WIDTH / 2;
				data->camera.y = row * BLOCK_SIZE - SCREEN_HEIGHT / 2;
				break;
			case 23:
				ent = new Bird(col * BLOCK_SIZE, row * BLOCK_SIZE, 100, 100, 2, 100, data);
				enemies.push_back(ent);
				break;
			case 39:
				ent = new Knight(col * BLOCK_SIZE, row * BLOCK_SIZE -100, 200, 200, 3, 100, data);
				enemies.push_back(ent);
				break;
			default:
				break;
			}
		}
	}
}


void World::UpdateWorld() {
	for (auto&& block : collidables) {
		if(!block->dead)
			block->update(this);
		
	}
	for (auto&& enemy : enemies) {
		if(!enemy->dead)
			enemy->update(this);
	}
	player->update(this);

}

void World::DrawWorld() {
	dest.x = src.x - data->camera.x;
	dest.y = src.y - data->camera.y;
	data->texmanager.Draw(background, src, dest, data->renderer);
	int buffer = 100;
	for (auto&& block : collidables) {
		if (block->position->x >= data->camera.x - buffer && block->position->x + block->width <= data->camera.x + data->camera.w + buffer &&
			block->position->y >= data->camera.y - buffer && block->position->y + block->height <= data->camera.y + data->camera.h + buffer) {
			block->draw();
		}
	}
	for (auto&& enemy : enemies) {
		if (enemy->position->x >= data->camera.x - buffer && enemy->position->x + enemy->width <= data->camera.x + data->camera.w + buffer &&
			enemy->position->y >= data->camera.y - buffer && enemy->position->y + enemy->height <= data->camera.y + data->camera.h + buffer) {
			enemy->draw();
		}
	}

	player->draw();

}