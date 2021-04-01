#include <iostream>
#include <SDL.h>
#include <SDL_image.h>

#include "repict.h"

#define STB_IMAGE_IMPLEMENTATION
#define STBI_NO_PSD
#define STBI_NO_TGA
#define STBI_NO_GIF
#define STBI_NO_HDR
#define STBI_NO_PIC
#define STBI_NO_PNM
#include "stb_image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

static int image_interface();

SDL_Surface* load_surface(std::string path);


SDL_Surface* surface = NULL;
SDL_Window* window = NULL;
SDL_Renderer* renderer;

static const std::string default_dir = "C:\\Users\\nate\\Documents\\_REPOS\\repict-visual\\";
static const std::string default_img = "lotr.png";
static const size_t WIN_WIDTH = 1200;
static const size_t WIN_HEIGHT = 900;
static const size_t WIN_IMG_X = 0;
static const size_t WIN_IMG_Y = 0;
static const int WIN_IMG_FRAME_BOX = 700;
static const int WIN_IMG_FRAME_SPACE = 20;

static const int FPS = 60;
static const double TIME_STEP = 1 / FPS / 1000;		//ms


int main(int argc, char** argv) {


	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		std::cout << "Error initializing SDL: " << SDL_GetError() << std::endl;
		return 1;
	}

	window = SDL_CreateWindow("Repict", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIN_WIDTH, WIN_HEIGHT, SDL_WINDOW_SHOWN);

	if (!window) {
		std::cout << "Error creating window: " << SDL_GetError() << std::endl;
		return 1;
	}

	surface = SDL_GetWindowSurface(window);

	if (!surface) {
		std::cout << "Error getting surface: " << SDL_GetError() << std::endl;
		return 1;
	}

	renderer = SDL_CreateRenderer(window, -1, 0);

	int img_flags = IMG_INIT_PNG;
	if (!(IMG_Init(img_flags) & img_flags)) {
		std::cout << "SDL_image init error: " << IMG_GetError() << "\n";
		return 1;
	}


	int error_code = -1;
	error_code = image_interface();

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return error_code;
}



static int image_interface() {

	bool exit_window = false;
	int error_code = 0;

	//SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, 255, 100, 255));
	//SDL_UpdateWindowSurface(window);

	SDL_Surface* display_img = NULL;
	SDL_Surface* edit_img = NULL;

	display_img = load_surface(default_dir + default_img);
	if (display_img == NULL) {
		return 1;
	}
	edit_img = load_surface(default_dir + default_img);
	if (edit_img == NULL) {
		return 1;
	}

	int display_width = 10;
	int display_height = 10;
	float img_ratio = ((float) display_img->w) / ((float) display_img->h);
	if (display_img->w >= display_img->h) {
		display_width = WIN_IMG_FRAME_BOX;
		display_height = (int)((float)display_width / img_ratio);
	}
	else {
		display_height = WIN_IMG_FRAME_BOX;
		display_width = (int)((float)display_width * img_ratio);
	}
	SDL_Texture* display_texture = SDL_CreateTextureFromSurface(renderer, display_img);
	SDL_Rect display_rect = 
		{ WIN_IMG_X, 
		WIN_IMG_Y, 
		display_width, 
		display_height};


	SDL_Texture* edit_texture = SDL_CreateTextureFromSurface(renderer, edit_img);
	SDL_Rect edit_rect =
		{ WIN_IMG_X,
		WIN_IMG_Y + display_height + WIN_IMG_FRAME_SPACE,
		display_width,
		display_height };

	SDL_RenderCopy(renderer, display_texture, NULL, &display_rect);
	SDL_RenderCopy(renderer, edit_texture, NULL, &edit_rect);
	SDL_RenderPresent(renderer);

	SDL_Event event;
	while (!exit_window) {
		while (SDL_PollEvent(&event) != 0) {
			if (event.type == SDL_QUIT) {
				exit_window = true;
			}
		}

		// untimed frame time
		SDL_Delay(TIME_STEP);
	}


	SDL_DestroyTexture(display_texture);
	SDL_FreeSurface(display_img);
	SDL_DestroyTexture(edit_texture);
	SDL_FreeSurface(edit_img);

	return error_code;
}



SDL_Surface* load_surface(std::string path) {
	SDL_Surface* opt_surface = NULL;
	SDL_Surface* load_surface = IMG_Load(path.c_str());
	if (load_surface == NULL) {
		std::cout << "Unable to load image " << path << "\nError: " << IMG_GetError() << "\n";
		return NULL;
	}
	opt_surface = SDL_ConvertSurface(load_surface, surface->format, 0);
	if (opt_surface == NULL) {
		std::cout << "Unable to optimize image " << path << "\nError: " << SDL_GetError() << "\n";
		return NULL;
	}
	SDL_FreeSurface(load_surface);
	return opt_surface;
}

