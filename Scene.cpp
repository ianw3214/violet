#include "Scene.h"

Scene::Scene(std::vector<std::string> inpSequence, std::string path, SDL_Surface* gSurface){

    // ASSUMES the input vector is not empty

    this->sequence = inpSequence;
    this->currentString = sequence[0];
    this->currentLine = 0;
    this->letters = IMG_Load("assets/letters.png");

    this->gSurface = gSurface;
    this->img = IMG_Load(path.c_str());

}

bool Scene::keyPress(){

    /*  return values:
        TRUE: The sequence isn't finished
        FALSE: The sequence has finished
    */

    currentLine++;

    if(currentLine >= sequence.size()){
        return false;
    }else{
        currentString = sequence.at(currentLine);
        std::cout << currentString << std::endl;
        return true;
    }

}

void Scene::render(){

    if (SDL_BlitSurface(img, nullptr, gSurface, nullptr) < 0) {
		std::cout << "Image unable to blit to surface, SDL_image ERROR : " << IMG_GetError() << std::endl;
    }
    loadLetters();
    return;

}

void Scene::loadLetters(){

    for(int i = 0; i < currentString.size(); i++){

        SDL_Rect thisRect = {};
        thisRect.w = 24;
        thisRect.h = 32;

        switch(currentString[i]){
            case 'A':
            case 'a':{
                thisRect.x = 0;
                thisRect.y = 0;
            } break;
            case 'B':
            case 'b':{
                thisRect.x = 24;
                thisRect.y = 0;
            } break;
            case 'C':
            case 'c':{
                thisRect.x = 48;
                thisRect.y = 0;
            } break;
            case 'D':
            case 'd':{
                thisRect.x = 72;
                thisRect.y = 0;
            } break;
            case 'E':
            case 'e':{
                thisRect.x = 96;
                thisRect.y = 0;
            } break;
            case 'F':
            case 'f':{
                thisRect.x = 120;
                thisRect.y = 0;
            } break;
            case 'G':
            case 'g':{
                thisRect.x = 144;
                thisRect.y = 0;
            } break;
            case 'H':
            case 'h':{
                thisRect.x = 168;
                thisRect.y = 0;
            } break;
            case 'I':
            case 'i':{
                thisRect.x = 192;
                thisRect.y = 0;
            } break;
            case 'J':
            case 'j':{
                thisRect.x = 216;
                thisRect.y = 0;
            } break;
            case 'K':
            case 'k':{
                thisRect.x = 0;
                thisRect.y = 32;
            } break;
            case 'L':
            case 'l':{
                thisRect.x = 24;
                thisRect.y = 32;
            } break;
            case 'M':
            case 'm':{
                thisRect.x = 48;
                thisRect.y = 32;
            } break;
            case 'N':
            case 'n':{
                thisRect.x = 72;
                thisRect.y = 32;
            } break;
            case 'O':
            case 'o':{
                thisRect.x = 96;
                thisRect.y = 32;
            } break;
            case 'P':
            case 'p':{
                thisRect.x = 120;
                thisRect.y = 32;
            } break;
            case 'Q':
            case 'q':{
                thisRect.x = 144;
                thisRect.y = 32;
            } break;
            case 'R':
            case 'r':{
                thisRect.x = 168;
                thisRect.y = 32;
            } break;
            case 'S':
            case 's':{
                thisRect.x = 192;
                thisRect.y = 32;
            } break;
            case 'T':
            case 't':{
                thisRect.x = 216;
                thisRect.y = 32;
            } break;
            case 'U':
            case 'u':{
                thisRect.x = 0;
                thisRect.y = 64;
            } break;
            case 'V':
            case 'v':{
                thisRect.x = 24;
                thisRect.y = 64;
            } break;
            case 'W':
            case 'w':{
                thisRect.x = 48;
                thisRect.y = 64;
            } break;
            case 'X':
            case 'x':{
                thisRect.x = 72;
                thisRect.y = 64;
            } break;
            case 'Y':
            case 'y':{
                thisRect.x = 96;
                thisRect.y = 64;
            } break;
            case 'Z':
            case 'z':{
                thisRect.x = 120;
                thisRect.y = 64;
            } break;
            case '!':{
                thisRect.x = 144;
                thisRect.y = 64;
            } break;
            case '.':{
                thisRect.x = 168;
                thisRect.y = 64;
            } break;
            case '?':{
                thisRect.x = 192;
                thisRect.y = 64;
            } break;
            case '\'':{
                thisRect.x = 216;
                thisRect.y = 64;
            } break;
            case ' ':{
                thisRect.x = 0;
                thisRect.y = 96;
            } break;
        }

        SDL_Rect gameRect = { 20 + (i%50)*24, 800 + (i/50)*32, 24, 32};

        if (SDL_BlitSurface(letters, &thisRect, gSurface, &gameRect) < 0) {
            std::cout << "Image unable to blit to surface, SDL_image ERROR : " << IMG_GetError() << std::endl;
        }

    }
    return;
}
