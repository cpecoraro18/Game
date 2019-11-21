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
	dest.x = 0;
	dest.y = 0;

}

Map::~Map() {
	printf("Deleting Map\n");
	for (auto block : collidables) {
		delete block;
	}

}

void Map::LoadCollidables(char* path) {
	data->texmanager.LoadTexture("Images/level1tileset.png", "tileset", data->renderer);
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
				block->loadtexture("tileset", type%8*32, layer*32);
				block->loadHitboxTexture("hitbox", 0, 0);
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

	dest.w = mapWidth*55;
	dest.h = mapHeight*55;
	src.w = mapWidth *32;
	src.h = mapHeight*32;
	data->texmanager.LoadTexture("Images/level1tilemap_Background.png","background", data->renderer);
	background = data->texmanager.GetTexture("background");

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
				ent->loadtexture("coin", 0, 0);
				collidables.push_back(ent);
				break;
			case 17:
				ent = new Spike(data, col * 55, row * 55, 55, 55, false);
				ent->loadtexture("tileset", type % 8 * 32, layer * 32);
				collidables.push_back(ent);
				break;
			case 19:
				ent = new Spike(data, col * 55, row * 55, 55, 55, true);
				ent->loadtexture("tileset", type % 8 * 32, layer * 32);
				collidables.push_back(ent);
				break;
			case 20:
				ent = new Key(data, col * 55, row * 55, 55, 55, 4, 100);
				ent->loadtexture("key", 0, 0);
				collidables.push_back(ent);
				break;
			case 21:
				ent = new Block(data, col * 55, row * 55, 55, 55);
				ent->loadtexture("tileset", type % 8 * 32, layer * 32);
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
	int buffer = 150;
	for (auto&& block : collidables) {
		if (block->position->x >= data->camera.x - buffer && block->position->x + block->width <= data->camera.x + data->camera.w + buffer &&
			block->position->y >= data->camera.y - buffer && block->position->y + block->height <= data->camera.y + data->camera.h + buffer) {
			block->draw();
			
			
		}
	}

}