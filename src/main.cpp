#include <iostream>
#include <SDL.h>


int main(int argc, char** argv) {

	SDL_Surface* surface = NULL;
	SDL_Window* window = NULL;

	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		std::cout << "Error initializing SDL: " << SDL_GetError() << std::endl;
		return 1;
	}

	window = SDL_CreateWindow("Repict", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 900, 600, SDL_WINDOW_SHOWN);

	if (!window) {
		std::cout << "Error creating window: " << SDL_GetError() << std::endl;
		return 1;
	}

	surface = SDL_GetWindowSurface(window);

	if (!surface) {
		std::cout << "Error getting surface: " << SDL_GetError() << std::endl;
		return 1;
	}

	SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, 255, 100, 255));
	SDL_UpdateWindowSurface(window);

	system("pause");

	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}