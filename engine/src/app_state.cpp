#include "app_state.h"

void AppState::quitApp(){quit = true;}

bool AppState::didQuit(){return quit;}

bool AppState::quit = false;

Uint32 AppState::pixelFormat = 0;

void AppState::setPixelFormat(Uint32 pf) { pixelFormat = pf; }

Uint32 AppState::getPixelFormat(){ return pixelFormat; }
