#include "utils.h"
#include <SDL2/SDL.h>
#include <iostream>
using namespace std;

void printRGBA(Uint32 pixel, const SDL_PixelFormat* format){
    Uint8 r = 0;
    Uint8 g = 0;
    Uint8 b = 0;
    Uint8 a = 0;
    SDL_GetRGBA(pixel, format, &r, &g, &b, &a);
    cout << "R:" << unsigned(r) << " G:" << unsigned(g) << " B:" << unsigned(b) << " A:" << unsigned(a) << endl;
}

bool compareRGBA(Uint32 pixela, Uint32 pixelb, const SDL_PixelFormat* format){
    Uint8 r = 0;
    Uint8 r2 = 0;
    Uint8 g = 0;
    Uint8 g2 = 0;
    Uint8 b = 0;
    Uint8 b2 = 0;
    Uint8 a = 0;
    Uint8 a2 = 0;
    SDL_GetRGBA(pixela, format, &r, &g, &b, &a);
    SDL_GetRGBA(pixelb, format, &r2, &g2, &b2, &a2);
    return(!(r!=r2||g!=g2||b!=b2||a!=a2));
}

