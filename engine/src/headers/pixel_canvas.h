#ifndef PIXEL_CANVAS_H
#define PIXEL_CANVAS_H

#include <memory>
#include "sprite.h"
#include <SDL2/SDL.h>
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include "resource_library.h"
#include "sprite_sheet.h"
#include "sprite_map.h"

using namespace std;

class PixelCanvas{
public:
    PixelCanvas(SDL_Renderer* renderer, SDL_Window* window);
    ~PixelCanvas();
    void free();
    void render();
    void clear(int r, int g, int b, int a);
    void shadeP(int x, int y, int r, int g, int b, int a);
    void addShader(void(*shaderFunc)(double x, double y, Uint32 u_time, Uint8* r, Uint8* g, Uint8* b, Uint8* a));
    void pset(int x, int y, int r, int g, int b, int a);
    void spr(string spriteName, int index, int x, int y);
    void rspr(string spriteName, int index, int x, int y, double angle, bool reverse);
    void rect(int x, int y, int w, int h, int r, int g, int b, int a);
    void rectFill(int x, int y, int w, int h, int r, int g, int b, int a);
    void circle(int x, int y, double rad, int r, int g, int b, int a);
    void circleFill(int x, int y, double rad, int r, int g, int b, int a);
    void line(int x1, int y1, int x2, int y2, int r, int g, int b, int a);
    void setTransparentColor(int r, int g, int b, int a);
    bool loadSpriteIndex(string path);
    void loadSpriteDirectory(string path);
    void loadSpriteMap(string path);
    void loadSpriteMapDirectory(string path);
    void loadSprite(string path);
    void unloadAllSprites();
    void unloadSprite(string name);
    void drawFromMap(string map, int mapX, int mapY, int w, int h, int drawX, int drawY);
    Uint32 writeBufferXY(int x, int y, Uint32 data);
private:
    shared_ptr<Sprite> getSprite(string spriteName, int index);    
    SDL_Renderer* mRenderer;
    SDL_Texture* mTexture;
    int pixelWidth;
    int pixelHeight;
    Uint32* pixelBuffer;
    int bufferLength;
    int bufferPitch;
    Uint32 transparentColor;
    SDL_PixelFormat* mappingFormat;
    map<int,pair<string,int>> spriteIndex;
    ResourceLibrary<SpriteSheet> spriteLibrary;
    ResourceLibrary<SpriteMap> mapLibrary;
    
};

#endif 

// Local Variables:
// mode: c++
// End:
