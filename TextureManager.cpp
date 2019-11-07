#include "TextureManager.h"
#include "SDL_image.h"
#include <stdio.h>

SDL_Texture* TextureManager::LoadTexture(const char* texture, GameDataRef data) {

	SDL_Surface* tempSurface = IMG_Load(texture);
	SDL_Texture* tex = SDL_CreateTextureFromSurface(data->renderer, tempSurface);

	SDL_FreeSurface(tempSurface);
	return tex;
}

void TextureManager::Draw(SDL_Texture* tex, SDL_Rect src, SDL_Rect dest, GameDataRef data) {
	SDL_RenderCopy(data->renderer, tex, &src, &dest);
}
