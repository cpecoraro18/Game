#include "Window.h"



Window::Window() {

}

Window::~Window() {

}

bool Window::init(const char* title, const int SCREEN_WIDTH, const int SCREEN_HEIGHT, bool fullscreen) {
	int flags = 0;

	if (fullscreen) {
		flags = SDL_WINDOW_FULLSCREEN;
	}
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
		printf("SDL could not initialize SDL_Error: %s\n", SDL_GetError());
		return false;
	}
	else {
		//create window
		gWindow = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 
			SCREEN_WIDTH, SCREEN_HEIGHT, flags);
		if (gWindow == NULL) {
			printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
			return false;
		}
		else {
			//create renderer
			gRenderer = SDL_CreateRenderer(gWindow, -1, 0);
			if (gRenderer == NULL) {
				printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
				return false;
			}
			//get window surface
			gScreenSurface = SDL_GetWindowSurface(gWindow);
			camera = { 0, 0, 400, 400 };
			
		}
	}
	return true;
}

bool Window::loadMedia() {
	return true;
}

void Window::close() {
	//Deallocate surface
	SDL_FreeSurface(gBackgroundImage);
	gBackgroundImage = NULL;

	//Destroy window
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	//destroy renderer
	SDL_DestroyRenderer(gRenderer);

	//Quit SDL subsystems
	SDL_Quit();
}

void Window::render(Map* map, Player* player) {

	SDL_RenderClear(gRenderer);
	map->DrawMap(gRenderer);
	

}

void Window::renderEntity(std::vector<class Entity*> entities) {
	for (auto&& ent : entities) {
		ent->draw(gRenderer);
		
	}
	SDL_RenderPresent(gRenderer);
	
}