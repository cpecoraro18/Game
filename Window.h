#pragma once

#ifndef SRC_WINDOW_H_
#define SRC_WINDOW_H_


#include "SDL.h"
#include "Entity.h"
#include "Playerh.h"
#include "Map.h"
#include <vector>


class Window {
public:

	Window();

	~Window();

	bool init(const char* title, const int SCREEN_WIDTH, const int SCREEN_HEIGHT, bool fullscreen);

	bool loadMedia();

	void close();

	void render(Map* map, Player* player);

	void renderEntity(std::vector<class Entity*> entities);

	SDL_Window* getWindow() { return gWindow; }

	SDL_Surface* getSurface() { return gScreenSurface; }

	SDL_Renderer* getRenderer() { return gRenderer; }

private:
	//The window we'll be rendering to
	SDL_Window* gWindow = NULL;

	//The surface contained by the window
	SDL_Surface* gScreenSurface = NULL;

	//The image we will load and show on the screen
	SDL_Surface* gBackgroundImage = NULL;

	SDL_Renderer* gRenderer = NULL;

	SDL_Rect camera;



};

#endif /* SRC_WINDOW_H_ */