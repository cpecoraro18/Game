#include "Map.h"
#include "TextureManager.h"
#include <iostream>


Map::Map() {
	src.x = 0;
	src.y = 0;

}

void Map::LoadMap(int arr[25][60], const char* background, std::vector<class Entity*> &entities) {

	//this->background = TextureManager::LoadTexture(background);


	int type = 0;
	for (int row = 0; row < 25; row++) {
		for (int col = 0; col < 60; col++) {
			type = arr[row][col];
			Block* block;
			switch (type) {
			case -1:
				block = new Block(col * 45, row * 45, 45, 45);
				block->loadtexture("Images/water.bmp");
				//entities.push_back(block);
				blocks.push_back(block);
				break;
			case 01:
				block = new Block(col * 45, row * 45, 45, 45);
				block->loadtexture("Images/map1_1.png");
				entities.push_back(block);
				blocks.push_back(block);
				break;
			case 00:

				block = new Block(col * 45, row * 45, 45, 45);
				block->loadtexture("Images/map1_0.png");
				entities.push_back(block);
				blocks.push_back(block);
				break;
			case 02:

				block = new Block(col * 45, row * 45, 45, 45);
				block->loadtexture("Images/map1_2.png");
				entities.push_back(block);
				blocks.push_back(block);
				break;

			default:
				break;
			}
		}
	}
}
void Map::DrawMap() {
	//SDL_RenderCopy(ren, background, NULL, NULL);
	for (auto&& block : blocks) {
		block->draw();
	}

}