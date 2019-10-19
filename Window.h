#pragma once

#ifndef SRC_WINDOW_H_
#define SRC_WINDOW_H_


#include "SDL.h"
#include "Entity.h"
#include "Player.h"
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

	//The window we'll be rendering to
	static SDL_Window* gWindow;

	//The surface contained by the window
	static SDL_Surface* gScreenSurface;

	static SDL_Renderer* gRenderer;

	static SDL_Rect camera;


private:
	
	//The image we will load and show on the screen
	SDL_Surface* gBackgroundImage = NULL;



};

#endif /* SRC_WINDOW_H_ */