#ifndef UTILS_H
#define UTILS_H

#include <SDL2/SDL.h>

void printRGBA(Uint32 pixel, const SDL_PixelFormat* format);
bool compareRGBA(Uint32 pixela, Uint32 pixelb, const SDL_PixelFormat* format);

#endif
