/*	No Comfort Game Jam Entry
	- made with SDL

  @Ian Wang 2016
*/

#include <iostream>
#include <string>
#include <vector>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>

#include "Game.h"
#include "Constants.h"

// function declarations
bool init(SDL_Window**, SDL_Surface**);
void close(SDL_Window*);

// entry point
int main(int argc, char* argv[]) {

	// SDL window to refer to
	SDL_Window* window = nullptr;

	// the surface contained by the window
	SDL_Surface * screenSurface = nullptr;

	// initialize the SDL window and screen surface
	// only play the game if all SDL subsystems start correctly
	if (init(&window, &screenSurface)) {
		Game * mainGame = new Game(window, screenSurface);
		mainGame->startGame();
    	close(window);
	}

	return 0;

}


// handles initialization of SDL subsystems
bool init(SDL_Window** window, SDL_Surface** surface) {

	// Initialization flag
	bool success = true;

	// Initialize SDL
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {	// if SDL failed to initialize
		std::cout << "SDL could not initialize, SDL ERROR: " << SDL_GetError() << std::endl;
		success = false;
	}
	else {
		// SDL initialization was successful
		*window = SDL_CreateWindow("Missile Dodge", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (*window == nullptr) {
			std::cout << "Window was not created!, SDL ERROR: " << SDL_GetError() << std::endl;
			success = false;
		}
		else {
			// window successfully created
			int imgFlags = IMG_INIT_PNG;
			if (!(IMG_Init(imgFlags)&imgFlags)) {
				// output the error
				std::cout << "SDL_Image could not initialize, SDL_image ERROR : " << IMG_GetError() << std::endl;
				success = false;
			}
			else {
				// get the window surface
				*surface = SDL_GetWindowSurface(*window);
			}

			// initialize mixer(audio) loading
			if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 1024) == -1) {
				std::cout << "SDL_Mixer could not initialize, SDL_mixer ERROR : " << Mix_GetError() << std::endl;
				success = false;
			}
		}
	}

	return success;

}

// exit function to quit SDL
void close(SDL_Window* window) {

	// Destroy the window
	SDL_DestroyWindow(window);
	window = nullptr;

	// quit SDL_mixer
	Mix_CloseAudio();

	// Quit SDL subsystems
	SDL_Quit();

}
