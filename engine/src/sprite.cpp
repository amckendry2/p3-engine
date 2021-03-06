#include "sprite.h"
#include <SDL2/SDL.h>
#include <vector>
using namespace std;

Sprite::Sprite() : width{0}, height{0} {};

Sprite::Sprite(SDL_Surface* loadedSurface, Uint32 dst_format){
    width = loadedSurface->w;
    height = loadedSurface->h;
    Uint32 buffer[width * height];
    SDL_ConvertPixels(width, height, loadedSurface->format->format,
		      loadedSurface->pixels, loadedSurface->pitch,
		      dst_format, &buffer, loadedSurface->pitch);
    rgbaVec.insert(rgbaVec.end(), &buffer[0], &buffer[width*height]);
}

Uint32 Sprite::accessXY(int x, int y){
    int i = (y * width) + x;
    return rgbaVec[i];
}



