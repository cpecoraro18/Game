#pragma once

#ifndef SRC_TEXTUREMANAGER_H_
#define SRC_TEXTUREMANAGER_H_
#include "SDL.h"

class TextureManager {
public:
	static SDL_Texture* LoadTexture(const char* fileName, SDL_Renderer* ren);

	static void Draw(SDL_Texture* tex, SDL_Renderer* ren, SDL_Rect src, SDL_Rect dest);
};

#endif /* SRC_TEXTUREMANAGER_H_ */