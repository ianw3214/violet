#pragma once

#include <iostream>
#include <string>
#include <vector>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "Constants.h"

class Tile{

public:
    Tile(SDL_Surface*, int, SDL_Surface*, SDL_Rect);
    void render();
private:
    SDL_Surface * gSurface;
    SDL_Rect blitRect;
    SDL_Rect gameRect;
    SDL_Surface * tileSheet;

    void loadRect(int);
};
