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

#include "Constants.h"

class Player{

public:
    Player(SDL_Surface*);
    void render();
    void move(int);
    int getX();
    int getY();
private:
    SDL_Surface * gSurface;
    int x, y;
    SDL_Rect blitRect;
    SDL_Rect surfaceRect;
    SDL_Surface * img;
};
