#include "event_handler.h"
#include <SDL2/SDL.h>
#include <map>
#include <string>

using namespace std;

EventHandler::EventHandler() : quit{false}{};

void EventHandler::handleEvents(){
    SDL_Event e;
    while(SDL_PollEvent(&e) != 0){
	if(e.type == SDL_QUIT){
	    quit = true;
	}
	if(e.type == SDL_KEYDOWN || e.type == SDL_KEYUP){
	    int sym = e.key.keysym.sym;
	    int val = (e.type == SDL_KEYDOWN) ? e.key.repeat : -1;
	    if(inputState.contains(sym)){
		inputState[sym] = val;
	    } else {
		inputState.insert(pair<int,int>{sym, val});
	    }
	}
    }
}

bool EventHandler::buttonPressed(string button){
    SDL_Keycode keycode = SDL_GetKeyFromName(button.c_str());
    if(inputState.contains(keycode)){
	return inputState[keycode] == 0;
    } else {
	return false;
    }
}

bool EventHandler::buttonDown(string button){
    SDL_Keycode keycode = SDL_GetKeyFromName(button.c_str());
    if(inputState.contains(keycode)){
	return inputState[keycode] != -1;
    } else {
	return false;
    }
}

int EventHandler::buttonHeld(string button){
    SDL_Keycode keycode = SDL_GetKeyFromName(button.c_str());
    if(inputState.contains(keycode)){
	return inputState[keycode];
    } else {
	return -1;
    }
}

bool EventHandler::gotQuit(){return quit;}
