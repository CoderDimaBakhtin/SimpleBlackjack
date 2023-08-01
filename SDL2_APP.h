#pragma once
#ifndef _SDL2_APP_H_
#define _SDL2_APP_H_



#include "Defines.h"
#include <SDL.h>
#include <SDL_image.h>
#include <memory>
#include<thread>
#include <chrono>
#include <string>
#include "Object.h"
#include "deck.h"
#include "Text.h"

#include"player.h"


//#include<windows.h>

class SDL2_APP {
private:
    bool Running = 1;
    SDL_Surface* Surf_Display;
    SDL_Window* window;
    SDL_Renderer* renderer;


    ///////////////
    SDL_Texture* texture;


    ////////////////////////////////
    std::shared_ptr<Object> colorobj;
    

    std::shared_ptr<Player> dealer;
    std::vector<std::shared_ptr<Player>> player;
 
    int PlayerCounter = 0;
    int NewGameCond = 0;
  
public:
	SDL2_APP();

    void NewGame();

	int OnExecute();

    void Winner();

    ~SDL2_APP();
public:

    bool OnInit();

    void OnEvent(SDL_Event* Event);

    void OnLoop();

    void OnRender();

    void OnCleanup();


};


#endif
