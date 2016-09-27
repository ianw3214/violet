#include "Tile.h"

Tile::Tile(SDL_Surface* gSurface, int tileNum, SDL_Surface * inpIMG, SDL_Rect gRect){

    this->tileSheet = inpIMG;
    this->gSurface = gSurface;
    this->gameRect = gRect;
    loadRect(tileNum);

}

void Tile::render(){
    if (SDL_BlitSurface(tileSheet, &blitRect, gSurface, &gameRect) < 0) {
		std::cout << "Image unable to blit to surface, SDL_image ERROR : " << IMG_GetError() << std::endl;
    }
    return;
}

void Tile::loadRect(int tileNum){

    int column = tileNum % 10;
    int row = tileNum / 10;

    this->blitRect = {
        column * TILE_WIDTH,
        row * TILE_HEIGHT,
        TILE_WIDTH,
        TILE_HEIGHT
    };

    return;

}
