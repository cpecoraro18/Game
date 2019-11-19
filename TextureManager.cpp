#include "TextureManager.h"
#include "SDL_image.h"
#include <stdio.h>

void TextureManager::LoadTexture(const char* texture, const char* name, SDL_Renderer* renderer) {

	SDL_Surface* tempSurface = IMG_Load(texture);
	SDL_Texture* tex = SDL_CreateTextureFromSurface(renderer, tempSurface);
	if (tex != NULL) {
		this->_textures[name] = tex;
	}
	SDL_FreeSurface(tempSurface);
}
SDL_Texture *TextureManager::GetTexture(const char* name) {
	return this->_textures.at(name);
}


void TextureManager::Draw(SDL_Texture* tex, SDL_Rect src, SDL_Rect dest, SDL_Renderer* renderer) {
	SDL_RenderCopy(renderer, tex, &src, &dest);
}

void TextureManager::Draw(SDL_Texture* tex, SDL_Rect src, SDL_Rect dest, SDL_Renderer* renderer, double angle) {
	SDL_RenderCopyEx(renderer, tex, &src, &dest, angle, NULL, SDL_FLIP_NONE);
}