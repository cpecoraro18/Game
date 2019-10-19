#include "Window.h"

SDL_Window* Window::gWindow;

//The surface contained by the window
SDL_Surface* Window::gScreenSurface;

SDL_Renderer* Window::gRenderer;

SDL_Rect Window::camera = { 0, 0, 400, 320 };

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
		Window::gWindow = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
			SCREEN_WIDTH, SCREEN_HEIGHT, flags);
		if (Window::gWindow == NULL) {
			printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
			return false;
		}
		else {
			//create renderer
			Window::gRenderer = SDL_CreateRenderer(gWindow, -1, 0);
			if (Window::gRenderer == NULL) {
				printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
				return false;
			}
			//get window surface
			Window::gScreenSurface = SDL_GetWindowSurface(Window::gWindow);
			Window::camera = { 0, 0, 400, 400 };

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
	SDL_DestroyWindow(Window::gWindow);
	gWindow = NULL;
	//destroy renderer
	SDL_DestroyRenderer(Window::gRenderer);

	//Quit SDL subsystems
	SDL_Quit();
}

void Window::render(Map* map, Player* player) {
	camera.x = player->getPosition().x-400;
	camera.y = player->getPosition().y-320;
	if (camera.x < 0) {
		camera.x = 0;
	}
	if (camera.y < 0) {
		camera.y = 0;
	}
	if (camera.x > 800) {
		camera.x = 800;
	}
	if (camera.y > 640) {
		camera.y = 640;
	}
	SDL_RenderClear(Window::gRenderer);
	map->DrawMap();
}

void Window::renderEntity(std::vector<class Entity*> entities) {
	for (auto&& ent : entities) {
		ent->draw();
	}
	SDL_RenderPresent(Window::gRenderer);
}