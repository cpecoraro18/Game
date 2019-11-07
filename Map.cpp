#include "Map.h"
#include "TextureManager.h"
#include "Coin.h"
#include "Key.h"
#include "Spike.h"
#include <iostream>
#include <fstream>


Map::Map(GameDataRef data): data(data) {
	src.x = 0;
	src.y = 0;

}

void Map::LoadCollidables(char* path) {

	std::ifstream inFile;
	inFile.open(path);
	if (!inFile) {
		printf("Unable to open file datafile.txt");
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
				block = new Block(data, col * 55, row * 55, 55, 55);
				layer = type / 8;
				block->loadtexture("Images/level1tileset.png", type%8*32, layer*32);
				collidables.push_back(block);
				break;
			}
		}
	}
}

void Map::LoadBackground(char* path) {
	std::ifstream inFile;
	inFile.open(path);
	if (!inFile) {
		printf("Unable to open file datafile.txt");
		exit(1);   // call system to stop
	}
	inFile >> mapWidth;
	inFile >> mapHeight;

	blocks.reserve(mapWidth*mapHeight);

	int type = 0;
	int layer;
	for (int row = 0; row < mapHeight; row++) {
		for (int col = 0; col < mapWidth; col++) {
			inFile >> type;
			Block* block;
			switch (type) {
			case -1:
				break;
			default:
				block = new Block(data, col * 55, row * 55, 55, 55);
				layer = type / 8;
				block->loadtexture("Images/level1tileset.png", type % 8 * 32, layer * 32);
				blocks.push_back(block);
				break;
			}
		}
	}

}

void Map::LoadCoins(char* path) {
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
			layer = type / 8;
			Entity* ent;
			switch (type) {
			case -1:
				break;
			case 16:
				ent = new Coin(data, col * 55, row * 55, 35, 35, 5, 100);
				ent->loadtexture("Images/Coin.png", 0, 0);
				collidables.push_back(ent);
				break;
			case 17:
				ent = new Spike(data, col * 55, row * 55, 55, 55, false);
				ent->loadtexture("Images/level1tileset.png", type % 8 * 32, layer * 32);
				collidables.push_back(ent);
				break;
			case 19:
				ent = new Spike(data, col * 55, row * 55, 55, 55, true);
				ent->loadtexture("Images/level1tileset.png", type % 8 * 32, layer * 32);
				collidables.push_back(ent);
				break;
			case 20:
				ent = new Key(data, col * 55, row * 55, 55, 55, 4, 100);
				ent->loadtexture("Images/key.png", 0, 0);
				collidables.push_back(ent);
				break;
			case 21:
				ent = new Block(data, col * 55, row * 55, 55, 55);
				ent->loadtexture("Images/level1tileset.png", type % 8 * 32, layer * 32);
				collidables.push_back(ent);
				break;
			default:
				break;
			}
		}
	}

}


void Map::UpdateMap(float dt) {
	for (auto&& block : blocks) {
		block->update(collidables, dt);
	}
	for (auto&& block : collidables) {
		block->update(collidables, dt);
		
	}

}

void Map::DrawMap(GameDataRef data) {
	//SDL_RenderCopy(ren, background, NULL, NULL);
	int buffer = 150;
	for (auto&& block : blocks) {
		if (block->position->x >= data->camera.x - buffer && block->position->x + block->width <= data->camera.x + data->camera.w + buffer &&
			block->position->y >= data->camera.y - buffer && block->position->y + block->height <= data->camera.y + data->camera.h + buffer) {
			block->draw();
		}
	}
	for (auto&& block : collidables) {
		if (block->position->x >= data->camera.x - buffer && block->position->x + block->width <= data->camera.x + data->camera.w + buffer &&
			block->position->y >= data->camera.y - buffer && block->position->y + block->height <= data->camera.y + data->camera.h + buffer) {
			block->draw();
		}
	}

}