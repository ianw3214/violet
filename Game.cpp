#include "Game.h"

Game::Game(SDL_Window * window, SDL_Surface * surface){

    this->gWindow = window;
    this->gSurface = surface;
    this->quit = false;
    this->scene = false;
    this->foundNote = false;
    this->player = new Player(surface);
    this->bgm = Mix_LoadWAV(bgm_path);
    this->gameOver = false;
    if (bgm_path == nullptr) {
		std::cout << "Music was not able to be played, Error: " << Mix_GetError() << std::endl;
    }

    tileSheet = IMG_Load("assets/tile_sheet.png");
    if(!tileSheet){
        std::cout << "ERROR" << IMG_GetError() << std::endl;
    }

}

void Game::startGame(){
    initMapSequence();
    loadMap();
    if (Mix_PlayChannel(-1, bgm, -1) == -1) {
    		std::cout << "Music was not able to be played, Error: " << Mix_GetError() << std::endl;
    }
    currentScene = new Scene({
        "Press space to interact...",
        "Use arrow keys to move..",
        "...",
        "Where am I?..",
        "This place seems kind of familiar..",
        "Maybe I should look around.."
    }, "assets/scenes/title.png", gSurface);
    scene = true;

    fade(0);

    while(!quit){
        tick();
    }
}

void Game::endGame(){

    fade(1);

    currentScene = new Scene({
        "Thanks for playing!",
        "Press Escape to quit the game..",
        "I don't really see why you would play again..",
        "Have a nice day!",
        "...",
        "...",
        "...",
        "...",
        "...",
        "...",
        "...",
        "...",
        "...",
        "...",
        "HARAMBE..",
        "I can join him now...",
        "...",
        "...",
        "...",
        "...",
        "...",
        "...",
        "okay seriously i got nothing now..",
        "...",
        "...",
        "...",
        "...",
        "...",
        "...",
        "...",
        "ha.. ",
        "harambe?",
        "...",
        "...",
        "...",
        "okay that was really it",
        "...",
        "...",
        "k bye...",
        "...",
        "it's gonna loop now",
        "so you should leave...",
        "...",
        "...",
        "you press escape to leave btw...",
        "...",
        "...",
        "..."
    }, "assets/scenes/credits.png", gSurface);
    scene = true;

    fade(0);

    while(!quit){
        tick();
    }
    return;
}

void Game::tick(){
    handleEvents();
    render();
    SDL_UpdateWindowSurface(gWindow);
    if(gameOver && currentScene==nullptr){
        endGame();
    }
}

void Game::handleEvents(){
    // handle events on queue
	while (SDL_PollEvent(&e) != 0) {
		// if the user quits
		if (e.type == SDL_QUIT) {
			// end the game
			quit = true;
		}
		else if (e.type == SDL_KEYDOWN) {
			switch(e.key.keysym.sym){
                case SDLK_ESCAPE:{
                    quit = true;
                } break;
                case SDLK_RIGHT:{
                    if(player->getX()+1 <= RIGHT_MARGIN && !scene) player->move(2);
                } break;
                case SDLK_LEFT:{
                    if(player->getX()-1 >= LEFT_MARGIN && !scene) player->move(4);
                } break;
                case SDLK_UP:{
                    if(player->getY()-1 >=  UPPER_MARGIN && !scene) player->move(1);
                } break;
                case SDLK_DOWN:{
                    if(player->getY()+1 <= LOWER_MARGIN && !scene) player->move(3);
                } break;
                case SDLK_SPACE:{
                    if(scene){
                        if(!currentScene->keyPress()){
                            currentScene = nullptr;
                            scene = false;
                        }
                    }else{
                        interact();
                    }
                } break;
            }
        }
    }
}

void Game::interact(){

    scene = true;

    int key = player->getY()*20 + player->getX();

    switch(eventSequence.at(key)){
        case 1:{
            currentScene = new Scene({
            "Theres not much to do here...",
            "Maybe I should try looking somewhere else!"
        }, "assets/scenes/player.png", gSurface);
        } break;
        case 2:{        // cat
            currentScene = new Scene({
                "It's a cat doll...",
                "I remember holding him in my sleep..",
                "He would protect me from the dark and tall        monsters!!",
                "The monsters got the better of him though...",
                "I never thought I would see him again!",
                "wonder how he ended up here..."
            }, "assets/scenes/cat.png", gSurface);
        } break;
        case 3:{        // seashell
            currentScene = new Scene({
                "It's a seashell!",
                "I've always loved seashells...",
                "There was this one time at a beach..",
                "I remember staying there for the whole day!",
                "I had a big collection of see shells..",
                "I don't remember who else was there though.."
            }, "assets/scenes/beach.png", gSurface);
        } break;
        case 4:{        // candle
            currentScene = new Scene({
                "The candle has been used...",
                "It's scent seems familiar",
                "I remember now!",
                "It was that dark and scary night..",
                "It kept us all safe from the noisy monsters..",
                "why is it here now?.."
            }, "assets/scenes/dark.png", gSurface);
        } break;
        case 5:{        // note -- TURNING POINT OF THE GAME
            currentScene = new Scene({
                "There's a note here...",
                "Dear violet..",
                "I don't know if this letter will ever reach you,",
                "but I want you to know that we have and will      always love you..",
                "You may not remember us in the future..",
                "but the few years I had with you were my best     moments..",
                "love.....",
                "mom",
                "P.S. If you ever forget us...",
                "We left something for you in the bookshelves"
            }, "assets/scenes/scroll.png", gSurface);
            this->foundNote = true;
        } break;
        case 6:{        // CD
            currentScene = new Scene({
                "It's an old record..",
                "I know this song!",
                "Wish you were here!",
                "I was at that concert!",
                "That was so long ago...",
                "How do I still remember that..."
            }, "assets/scenes/player.png", gSurface);
        } break;
        case 7:{        // floor drawing
            currentScene = new Scene({
                "There is a crayon drawing of godzilla on the      floor..",
                "I think i drew this!",
                "Who else could draw such a magnificent beast..",
                "I think I was in quite some trouble though.."
            }, "assets/scenes/player.png", gSurface);
        } break;
        case 8:{        // broken glass
            currentScene = new Scene({
                "I should avoid the broken glass on the floor",
                "looks like someone tried to play with a bottle of vodka",
                "I never really like vodka...",
                "Dad used to drink a lot though!.."
            }, "assets/scenes/player.png", gSurface);
        } break;
        case 9: {         // gun
            currentScene = new Scene({
                "Theres a gun on the floor...",
                "It's quite old. must have been used a lot...",
                "............",
                "............",
                "............",
                "It's all......",
                "coming back to me now...",
                "why..",
                "why am i here..."
            }, "assets/scenes/gun.png", gSurface);
        } break;
        case 10:{       // bookshelves
            if(foundNote){
                currentScene = new Scene({
                "Theres a small space between these books...",
                "Is that...",
                "...",
                "...",
                "...",
                "...",
                "..."
            }, "assets/scenes/photo.png", gSurface);
            this->gameOver = true;
            }else{
                currentScene = new Scene({
                    "Theres a lot of books here...",
                    "They have gathered quite a bit of dust"
                }, "assets/scenes/player.png", gSurface);
            }
        } break;
        case 11:{       // CLOCK
            currentScene = new Scene({
                "I remember this clock...",
                "I used to count the ticks when I slept..",
                "I usually got to around two hundred...",
                "and then I would close my eyes..",
                "and the warmth around me would put me to sleep.."
            }, "assets/scenes/player.png", gSurface);
        } break;
        case 12:{       // BASEBALL
            currentScene = new Scene({
                "It's a baseball and a bat...",
                "I used to play catch all the time..",
                "I remember mom telling us to be careful..",
                "Then I scraped my knees.."
            }, "assets/scenes/player.png", gSurface);
        } break;
        case 13:{       // BOOK
            currentScene = new Scene({
                "It's an old storybook...",
                "The three little pigs...",
                "I think I played the little pig once..",
                "Dad played the big bad wolf..",
                "Mom was a pig like me..",
                "Why did that ever stop..."
            }, "assets/scenes/player.png", gSurface);
        } break;
        case 14:{       // PIGGY BANK
            currentScene = new Scene({
                "It's a piggy bank...",
                "I used to have one too...",
                "I saved up a coin every day",
                "I promised mom I would buy her new clothes..",
                "And dad I would buy him a nice house",
                ".........."
            }, "assets/scenes/player.png", gSurface);
        } break;
        case 15:{       // WOOD BLOCKS
            currentScene = new Scene({
                "These were the wood blocks I used to play with!",
                "we couldn't afford legos...",
                "I tried to make nice houses out of them..",
                "I asked mom if she wanted to live in it..",
                "She said that would be nice.."
            }, "assets/scenes/player.png", gSurface);
        } break;
        case 16: {      // PAN
            currentScene = new Scene({
                "There's a pan on the floor..",
                "Mom used to cook all sorts of good food..",
                "Dad would complain it's too healthy..",
                "Mom said it balanced out the drinking..",
                "I learned how to cook too!..",
                "Mom taught me!..",
                "We used this pot...",
                "......"
            }, "assets/scenes/player.png", gSurface);
        } break;
    }

    return;

}

void Game::render(){
    for(int i = 0; i < tileMap.size(); i++){
        tileMap.at(i).render();
    }
    player->render();
    if(scene){
        currentScene->render();
    }
}

void Game::initMapSequence(){

    this->tileSequence = {
        22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 18, 23, 13, 13, 13, 13, 13, 13, 14,
        1, 0, 0, 21, 0, 25, 0, 0, 0, 0, 0, 8, 10, 10, 10, 10, 10, 10, 10, 14,
        1, 0, 3, 20, 0, 0, 0, 0, 20, 0, 0, 8, 29, 10, 10, 28, 10, 10, 10, 14,
        1, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 8, 10, 10, 10, 10, 10, 10, 10, 14,
        1, 21, 0, 0, 0, 0, 0, 21, 0, 0, 0, 8, 10, 10, 10, 10, 12, 10, 10, 14,
        1, 0, 21, 0, 0, 0, 0, 0, 0, 0, 0, 8, 10, 10, 11, 10, 10, 17, 10, 14,
        1, 0, 0, 24, 0, 0, 0, 5, 0, 0, 0, 8, 10, 10, 10, 10, 10, 10, 10, 15,
        1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 9, 9, 9, 9, 9, 19,
        1, 26, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
        1, 0, 20, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 21, 0, 0, 0, 0, 1,
        1, 20, 0, 2, 0, 0, 0, 0, 0, 2, 0, 21, 0, 0, 6, 0, 0, 0, 0, 1,
        1, 0, 21, 0, 4, 0, 20, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 1,
        1, 2, 0, 0, 0, 0, 0, 20, 27, 0, 0, 0, 0, 0, 0, 0, 0, 21, 0, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
    };

    this->eventSequence = {
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 1, 1, 1, 1, 11, 1, 1, 1, 1, 1, 1, 1, 1, 1, 10, 10, 10, 10, 0,
        0, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 16, 1, 1, 15, 1, 1, 1, 0,
        0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0,
        0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 8, 1, 1, 0,
        0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 7, 1, 1, 9, 1, 0,
        0, 1, 1, 12, 1, 1, 1, 4, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0,
        0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0,
        0, 13, 1, 1, 1, 1, 1, 1, 6, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0,
        0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0,
        0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 5, 1, 1, 1, 1, 0,
        0, 1, 1, 1, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0,
        0, 1, 1, 1, 1, 1, 1, 1, 14, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
    };

    return;
}

void Game::loadMap(){
    for(int i = 0; i < tileSequence.size(); i++){
        int row = i / MAP_WIDTH;
        int column = i % MAP_WIDTH;
        SDL_Rect tempRect = {
            column * TILE_WIDTH,
            row * TILE_HEIGHT,
            TILE_WIDTH,
            TILE_HEIGHT
        };
        tileMap.push_back(Tile(gSurface, tileSequence.at(i), tileSheet, tempRect));
    }
}

void Game::fade(int key) {

	// time variables to help fade in function stay within a time frame
	unsigned int bTick, cTick;
	unsigned int time = 2000;

	// black image to cover the screen with
	SDL_Surface * temp;
	temp = IMG_Load("assets/BLACK.png");
	if (!temp) {	// if the image failed to load
					// output the error
		std::cout << "Failed to load image, SDL_image ERROR : " << IMG_GetError() << std::endl;
	}

	// update the alpha values depending on the difference in time elapsed
	bTick = SDL_GetTicks();
	cTick = bTick;
	while ((cTick - bTick) < time) {

		// render the base menu first
		render();

		// set the alpha depenidng on time elapsed
		// if key is 0, fade in; if key is 1, fade out
		if (key == 0) {
			SDL_SetSurfaceAlphaMod(temp, 255 - ((float)cTick - (float)bTick) / (float)time * 255);
		}
		if (key == 1) {
			SDL_SetSurfaceAlphaMod(temp, ((float)cTick - (float)bTick) / (float)time * 255);
		}
		if (SDL_BlitSurface(temp, nullptr, gSurface, nullptr) < 0) {
			// output the error
			std::cout << "Image unable to blit to surface, SDL_image ERROR : " << IMG_GetError() << std::endl;
		}

		SDL_UpdateWindowSurface(gWindow);

		// update the current tick value
		cTick = SDL_GetTicks();
	}

	return;

}
