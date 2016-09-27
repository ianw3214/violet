/*	No Comfort Game Jam Entry
	- made with SDL

  @Ian Wang 2016
*/

#pragma once

#include <iostream>
#include <string>
#include <vector>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>

#include "Tile.h"
#include "Player.h"
#include "Scene.h"

class Game{

public:
	Game(SDL_Window*, SDL_Surface*);	// constructor
	void startGame();
	void endGame();
private:
	SDL_Window * gWindow;
	SDL_Surface * gSurface;
	Player * player;
	Scene * currentScene;
	SDL_Event e;

	void tick();
	void handleEvents();
	void interact();
	void render();

	SDL_Surface * tileSheet;
	SDL_Surface * sceneSprite;
	std::vector<Tile> tileMap;
	std::vector<int> eventSequence;
	std::vector<int> tileSequence;
	void initMapSequence();
	void loadMap();
	void fade(int);

	bool quit, scene, foundNote, gameOver;

	Mix_Chunk * bgm;
};
