#include "Map.h"
#include "TextureManager.h"
#include "Coin.h"
#include "Key.h"
#include "Spike.h"
#include "EndLevel.h"
#include <iostream>
#include <fstream>


Map::Map(GameDataRef data): data(data) {
	src.x = 0;
	src.y = 0;
	dest.x = 0;
	dest.y = 0;

}

Map::~Map() {
	printf("Deleting Map\n");
	for (auto block : collidables) {
		delete block;
	}

}

void Map::LoadCollidables(std::string path) {
	std::ifstream inFile;
	inFile.open(path);
	if (!inFile) {
		printf("Unable to open file %s", path.c_str());
		exit(1);   // call system to stop
	}
	inFile >> mapWidth;
	inFile >> mapHeight;
	collidables.reserve(mapWidth*mapHeight);
	int type = 0;
	int layer;
	for (int row = 0; row < mapHeight; row++) {
		for (int col = 0; col < mapWidth; col++) {
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

void Map::LoadBackground(std::string path, std::string level) {
	std::ifstream inFile;
	inFile.open(path);
	if (!inFile) {
		printf("Unable to open file datafile.txt");
		exit(1);   // call system to stop
	}
	inFile >> mapWidth;
	inFile >> mapHeight;

	dest.w = mapWidth* BLOCK_SIZE;
	dest.h = mapHeight* BLOCK_SIZE;
	src.w = mapWidth * BLOCK_SIZE;
	src.h = mapHeight* BLOCK_SIZE;
	data->texmanager.LoadTexture(level,"background", data->renderer);
	background = data->texmanager.GetTexture("background");

}

void Map::LoadCoins(std::string path) {
	std::ifstream inFile;
	inFile.open(path);
	if (!inFile) {
		printf("Unable to open file datafile.txt");
		exit(1);   // call system to stop
	}
	inFile >> mapWidth;
	inFile >> mapHeight;

	int type = 0;
	int layer;
	for (int row = 0; row < mapHeight; row++) {
		for (int col = 0; col < mapWidth; col++) {
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
			case 52:
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


void Map::UpdateMap(float dt) {
	for (auto&& block : collidables) {
		block->update(collidables, dt);
		
	}

}

void Map::DrawMap() {
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

}