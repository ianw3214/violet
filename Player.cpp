#include "Player.h"

Player::Player(SDL_Surface * gSurface){

    this->x = 1;
    this->y = 2;
    this->gSurface = gSurface;

    surfaceRect = {
        this->x * TILE_WIDTH,
        this->y * TILE_HEIGHT,
        PLAYER_WIDTH,
        PLAYER_HEIGHT
    };

    blitRect = { 128, 0, PLAYER_WIDTH, PLAYER_HEIGHT};

    img = IMG_Load("assets/player_sheet.png");
    if(!img){
        std::cout << "ERROR" << IMG_GetError() << std::endl;
    }

}

void Player::render(){

    SDL_Rect tempRect = surfaceRect;
    tempRect.y -= 64;

    if (SDL_BlitSurface(img, &blitRect, gSurface, &tempRect) < 0) {
		std::cout << "Image unable to blit to surface, SDL_image ERROR : " << IMG_GetError() << std::endl;
    }

    return;

}

int Player::getX(){ return this->x; }
int Player::getY(){ return this->y; }

void Player::move(int dir){
    /*  DIRECTIONS:
        1 - NORTH
        2 - EAST
        3 - SOUTH
        4 - WEST

        ASSUMES COLLISIONS ETC... ALREADY ACCOUNTED FOR
    */
    switch(dir){
        case 1:{
            this->y--;
            blitRect = { 0, 0, PLAYER_WIDTH, PLAYER_HEIGHT};
        }break;
        case 2:{
            this->x++;
            blitRect = { 64, 0, PLAYER_WIDTH, PLAYER_HEIGHT};
        }break;
        case 3:{
            this->y++;
            blitRect = { 128, 0, PLAYER_WIDTH, PLAYER_HEIGHT};
        }break;
        case 4:{
            this->x--;
            blitRect = { 192, 0, PLAYER_WIDTH, PLAYER_HEIGHT};
        }break;
        default:{
            std::cout << "NOTHING HAPPENED" << std::endl;
        }break;
    }

    // UPDATE THE SURFACE RECTANGLE
    surfaceRect = {
        this->x * TILE_WIDTH,
        this->y * TILE_HEIGHT,
        PLAYER_WIDTH,
        PLAYER_HEIGHT
    };

    return;

}
