#pragma once

#ifndef SRC_TEXTUREMANAGER_H_
#define SRC_TEXTUREMANAGER_H_
#include "SDL.h"
#include "Game.h"

class TextureManager {
public:
	static SDL_Texture* LoadTexture(const char* fileName, GameDataRef data);

	static void Draw(SDL_Texture* tex, SDL_Rect src, SDL_Rect dest, GameDataRef data);
};

#endif /* SRC_TEXTUREMANAGER_H_ */