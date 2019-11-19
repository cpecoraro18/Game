#pragma once

#ifndef SRC_TEXTUREMANAGER_H_
#define SRC_TEXTUREMANAGER_H_
#include "SDL.h"
#include <map>

class TextureManager {
public:
	void LoadTexture(const char* fileName, const char* name, SDL_Renderer* renderer);
	SDL_Texture* GetTexture(const char* name);

	void Draw(SDL_Texture* tex, SDL_Rect src, SDL_Rect dest, SDL_Renderer* renderer);

	void Draw(SDL_Texture* tex, SDL_Rect src, SDL_Rect dest, SDL_Renderer* renderer, double angle);
private:
	std::map<const char*, SDL_Texture*> _textures;

};

#endif /* SRC_TEXTUREMANAGER_H_ */