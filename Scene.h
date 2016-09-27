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

class Scene{

public:
    Scene(std::vector<std::string>, std::string, SDL_Surface*);
    bool keyPress();
    void render();
private:
    SDL_Surface * img;
    SDL_Surface * gSurface;
    SDL_Surface * letters;

    std::vector<std::string> sequence;
    std::string currentString;
    int currentLine;

    void loadLetters();
};
