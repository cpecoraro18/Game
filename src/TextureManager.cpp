#include "TextureManager.h"
#include "SDL_image.h"
#include <stdio.h>

SDL_Texture* TextureManager::LoadTexture(const char* texture, SDL_Renderer* ren) {

	SDL_Surface* tempSurface = IMG_Load(texture);
	SDL_Texture* tex = SDL_CreateTextureFromSurface(ren, tempSurface);

	SDL_FreeSurface(tempSurface);
	return tex;


}

void TextureManager::Draw(SDL_Texture* tex, SDL_Renderer* ren, SDL_Rect src, SDL_Rect dest) {

	SDL_RenderCopy(ren, tex, &src, &dest);


}
