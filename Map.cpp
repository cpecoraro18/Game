#include "Map.h"
#include "TextureManager.h"
#include "SDL_image.h"
#include <iostream>


Map::Map() {
	src.x = 0;
	src.y = 0;

}

void Map::LoadMap(SDL_Renderer* ren, int arr[20][25], const char* background, std::vector<class Entity*> &entities) {

	this->background = TextureManager::LoadTexture(background, ren);
	

	int type = 0;
	for (int row = 0; row < 20; row++) {
		for (int col = 0; col < 25; col++) {
			type = arr[row][col];
			Block* block;
			switch (type) {
			case 0:
				break;
			case 1:
				block = new Block(col * 32, row * 32, 32, 32);
				block->loadtexture("Images/grass.bmp", ren);
				entities.push_back(block);
				blocks.push_back(block);
				break;
			case 2:
				block = new Block(col * 32, row * 32, 32, 32);
				block->loadtexture("Images/dirt.bmp", ren);
				entities.push_back(block);
				blocks.push_back(block);
				break;
			case 3:
				
				block = new Block(col * 32, row * 32, 32, 32);
				block->loadtexture("Images/cloud.bmp", ren);
				entities.push_back(block);
				blocks.push_back(block);
				break;

			default:
				break;
			}
		}
	}
}
void Map::DrawMap(SDL_Renderer* ren) {
	SDL_RenderCopy(ren, background, NULL, NULL);
	for (auto&& block : blocks) {
		block->draw(ren);
	}

}