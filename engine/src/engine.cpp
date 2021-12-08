#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <stdio.h>
#include <string>

#include "engine.h"

Engine::Engine():
    appWindow{NULL},
    appRenderer{NULL}
{
    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0){
	printf("SDL could not initialize. Error: %s\n", SDL_GetError());
    }
    
    if(!(appWindow = SDL_CreateWindow("P3", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 512, 512, SDL_WINDOW_SHOWN))){
	printf("SDL could not create window. Error: %s\n", SDL_GetError());
    }
    
    if(!(appRenderer = SDL_CreateRenderer(appWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC))){
	printf("SDL could not create Renderer. Error: %s\n");
    }
    
    if(!IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG){
	printf("SDL could not initialize image processing. Error: %s\n", IMG_GetError());
    }

    if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0){
	printf("SDL could not initialize audio. Error: %s\n", Mix_GetError());
    }
    
}

Engine::~Engine(){close();}

void Engine::close(){
    SDL_DestroyRenderer(appRenderer);
    SDL_DestroyWindow(appWindow);
    appRenderer = NULL;
    appWindow = NULL;
    SDL_Quit();
}

SDL_Renderer* Engine::getRenderer(){
    return appRenderer;
}

SDL_Window* Engine::getWindow(){
    return appWindow;
}

void Engine::render(){
    SDL_RenderPresent(appRenderer);
}



