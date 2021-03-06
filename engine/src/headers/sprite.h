#ifndef SPRITE_H
#define SPRITE_H

#include <SDL2/SDL.h>
#include <vector>

using namespace std;

struct Sprite {
    int width;
    int height;
    vector<Uint32> rgbaVec;
    Sprite();
    Sprite(SDL_Surface* imgSurface, Uint32 format);
    Uint32 accessXY(int x, int y);
};

#endif
