#include "sprite.h"
#include "sprite_sheet.h"
#include "pixel_canvas.h"
#include "utils.h"
#include "resource_manager.h"
#include "app_state.h"
#include "sprite_map.h"
#include <math.h>
#include <map>
#include <regex>
#include <vector>
#include <string>
#include <filesystem>
#include <fstream>
#include <SDL2/SDL_image.h>

using namespace std;

PixelCanvas::PixelCanvas(SDL_Renderer* renderer, SDL_Window* window): mRenderer{renderer}
{
    mTexture = SDL_CreateTexture(mRenderer, SDL_GetWindowPixelFormat(window), SDL_TEXTUREACCESS_STATIC, 128, 128);
    Uint32 format;
    SDL_QueryTexture(mTexture, &format, nullptr, &pixelWidth, &pixelHeight);
    mappingFormat = SDL_AllocFormat(SDL_GetWindowPixelFormat(window));
    pixelBuffer = new Uint32[pixelWidth * pixelHeight];
    bufferLength = pixelWidth * pixelHeight;
    bufferPitch = pixelWidth * sizeof(Uint32);
    transparentColor = SDL_MapRGBA(mappingFormat, 0, 0, 0, 255);
};

PixelCanvas::~PixelCanvas(){ free(); }

void PixelCanvas::free(){
    if(mappingFormat != NULL){
	SDL_FreeFormat(mappingFormat);
	mappingFormat = NULL;
    }
    if(mTexture != NULL){
	SDL_DestroyTexture(mTexture);
	mTexture = NULL;
    }
    spriteLibrary.unloadAll();
    mapLibrary.unloadAll();
    delete[](pixelBuffer);
    pixelBuffer = NULL;
}

void PixelCanvas::render() {
    SDL_UpdateTexture(mTexture, NULL, pixelBuffer, bufferPitch);
    SDL_RenderCopy(mRenderer, mTexture, NULL, NULL);
}

void PixelCanvas::setTransparentColor(int r, int g, int b, int a){
    transparentColor = SDL_MapRGBA(mappingFormat, r, g, b, a);
}

void PixelCanvas::clear(int r, int g, int b, int a){
    Uint32 colorType = SDL_MapRGBA(mappingFormat, r, g, b, a);
    for(int i = 0; i < bufferLength; i++){
        pixelBuffer[i] = colorType;
    }
}

void PixelCanvas::addShader(void(*shaderFunc)(double x, double y, Uint32 u_time, Uint8* r, Uint8* g, Uint8* b, Uint8* a)){
    for(int ix = 0; ix < pixelWidth; ix++){
	for(int iy = 0; iy < pixelHeight; iy++){
	    Uint8 rval = 0;
	    Uint8 gval = 0;
	    Uint8 bval = 0;
	    Uint8 aval = 0;
	    Uint32 t = SDL_GetTicks();
	    double stX = (float)ix / (float)pixelWidth;
	    double stY = (float)iy / (float)pixelHeight;
	    if(stX==.5 && stY==.5)
		cout << "add shader before: " << (int)bval << endl;
	    shaderFunc(stX, stY, t, &rval, &gval, &bval, &aval);
	    if(stX==.5 && stY==.5)
		cout << "add shader after: " << (int)bval << endl;
	    shadeP(ix, iy, rval, gval, bval, aval);
	}
    }
}

void PixelCanvas::shadeP(int x, int y, int r, int g, int b, int a){
    int i = y * pixelWidth + x;
    Uint8 rval;
    Uint8 gval;
    Uint8 bval;
    Uint8 aval;
    SDL_GetRGBA(pixelBuffer[i], mappingFormat, &rval, &gval, &bval, &aval);
    int rsum = clamp((int)rval + r, 0, 255);
    int gsum = clamp((int)gval + g, 0, 255);
    if(x == 64 && y == 64)
	cout << "shadep before: " << (int)bval << endl;
    int bsum = clamp((int)bval + b, 0, 255);
    if(x==64 && y == 64){
	cout << "shadep after: " << (int)bsum << endl;
	cout << "shadep Uint8 after: " << (Uint8)bsum << endl;
    }
    int asum = clamp((int)aval + a, 0, 255);
    pixelBuffer[i] = SDL_MapRGBA(mappingFormat, rsum, gsum, bsum, asum);
}

void PixelCanvas::pset(int x, int y, int r, int g, int b, int a){
    // int i = y * pixelWidth + x;
    // pixelBuffer[i] = SDL_MapRGBA(mappingFormat, r, g, b, a);
    writeBufferXY(x, y, SDL_MapRGBA(mappingFormat, r, g, b, a));
}

shared_ptr<Sprite> PixelCanvas::getSprite(string spriteName, int index){
    shared_ptr<SpriteSheet>ssptr = spriteLibrary.get(spriteName);
    if(ssptr == nullptr)
	return nullptr;
    SpriteSheet ss = *ssptr;
    if(index < 0 || index >= ss.size()){
    	cout << "Bad sprite index!" << endl;
    	return nullptr;
    }
    return ss[index];
}

void PixelCanvas::spr(string spriteName, int index, int x0, int y0){
    shared_ptr<Sprite> spr = getSprite(spriteName, index);
    for (int i = 0; i < spr->width * spr->height; i++){
	Uint32 pixel = spr->rgbaVec[i];
	if(!compareRGBA(pixel, transparentColor, mappingFormat)){	    
	    int x = i % spr->width;
	    int y = floor(i / spr->width);
	    int xPos = x0 + x;
	    int yPos = y0 + y;
	    writeBufferXY(x0 + x, y0 + y, pixel);
	}
    }
}


void PixelCanvas::rspr(string spriteName, int index, int drawX, int drawY, double angle, bool reverse){
    shared_ptr<Sprite> spr = getSprite(spriteName, index);
    float w2 = spr->width / 2;
    float dxcol = cos(angle);
    float dycol = sin(angle);
    float dxrow = dycol;
    float dyrow = -dxcol;
    float init_x = w2 - ((w2 - 0.5) * dycol + (w2 - 0.5) * dxcol);
    float init_y = w2 - ((w2 - 0.5) * dyrow + (w2 - 0.5) * dxrow);
    if(!reverse){
	init_y = spr->width - init_y;
	dycol *= -1;
	dyrow *= -1;
    }
    for(int xi = 0; xi < spr->width; xi++){
	float x = init_x;
	float y = init_y;
	for(int yi = 0; yi < spr->height; yi++){
	    int xFloor = floor(x);
	    int yFloor = floor(y);
	    if(clamp(xFloor, 0, spr->width - 1) == xFloor && clamp(yFloor, 0, spr->height - 1) == yFloor){
		Uint32 colorData = spr->accessXY(xFloor, yFloor);
		if(!compareRGBA(colorData, transparentColor, mappingFormat)){
		    writeBufferXY(drawX + xi, drawY + yi, colorData);
		}
	    }
	    x += dxrow;
	    y += dyrow;
	}
	init_x += dxcol;
	init_y += dycol;
    }
}

void PixelCanvas::rect(int x, int y, int w, int h, int r, int g, int b, int a){
    line(x, y, x + w, y, r, g, b, a);
    line(x + w, y, x + w, y + h, r, g, b, a);
    line(x + w, y + h, x, y + h, r, g, b, a);
    line(x, y + h, x, y, r, g, b, a);
}

void PixelCanvas::rectFill(int x, int y, int w, int h, int r, int g, int b, int a){
    for(int xx = x; xx <= x + w; xx++){
	for(int yy = y; yy <= y + h; yy++){
	    pset(xx, yy, r, g, b, a);
	}
    }
}

void PixelCanvas::circle(int x, int y, double rad, int r, int g, int b, int a){
    // from : https://www.geeksforgeeks.org/bresenhams-circle-drawing-algorithm/
    auto drawOctants = [this, r, g, b, a](int xc, int yc, int x, int y)
		 {
		     pset(xc+x, yc+y, r, g, b, a);
		     pset(xc-x, yc+y, r, g, b, a);
		     pset(xc+x, yc-y, r, g, b, a);
		     pset(xc-x, yc-y, r, g, b, a);
		     pset(xc+y, yc+x, r, g, b, a);
		     pset(xc-y, yc+x, r, g, b, a);
		     pset(xc+y, yc-x, r, g, b, a);
		     pset(xc-y, yc-x, r, g, b, a);
		 };
    int cur_x = 0;
    int cur_y = rad;
    int d = 3 - 2 * rad;
    drawOctants(x, y, cur_x, cur_y);
    while (cur_y >= cur_x){
	cur_x++;
	if(d > 0){
	    cur_y--;
	    d = d + 4 * (cur_x - cur_y) + 10;
	} else {
	    d = d + 4 * cur_x + 6;
	}
	drawOctants(x, y, cur_x, cur_y);
    }
}

void PixelCanvas::circleFill(int x, int y, double rad, int r, int g, int b, int a){
    circle(x, y, rad, r, g, b, a);
    for (int xx = -rad; xx <= rad; xx++){
	for (int yy = -rad; yy <= rad; yy++){
	    if(xx * xx + yy * yy <= rad * rad){
		pset(xx + x, yy + y, r, g, b, a);
	    }
	}
    }
}

void PixelCanvas::line(int x1, int y1, int x2, int y2, int r, int g, int b, int a){
    auto plotLow = [this, r, g, b, a](int x0, int y0, int x1, int y1)
			{
			    int dx = x1 - x0;
			    int dy = y1 - y0;
			    int yi = 1;
			    if(dy < 0){
				yi = -1;
				dy = -dy;
			    }
			    int d = (2 * dy) - dx;
			    int y = y0;
			    for(int x = x0; x <= x1; x++){
				pset(x, y, r, g, b, a);
				if(d > 0){
				    y = y + yi;
				    d = d + (2 * (dy - dx));
				} else {
				    d = d + 2 * dy;
				}
			    }
			};
    auto plotHigh = [this, r, g, b, a](int x0, int y0, int x1, int y1)
			{
			    int dx = x1 - x0;
			    int dy = y1 - y0;
			    int xi = 1;
			    if(dx < 0){
				xi = -1;
				dx = -dx;
			    }
			    int d = (2 * dx) - dy;
			    int x = x0;
			    for(int y = y0; y <= y1; y++){
				pset(x, y, r, g, b, a);
				if(d > 0){
				    x = x + xi;
				    d = d + (2 * (dx - dy));
				} else {
				    d = d + 2 * dx;
				}
			    }
			};

    if(abs(y2 - y1) < abs(x2 - x1)){
	if(x1 > x2){
	    plotLow(x2, y2, x1, y1);
	} else {
	    plotLow(x1, y1, x2, y2);
	}
    } else {
	if(y1 > y2){
	    plotHigh(x2, y2, x1, y1);
	} else {
	    plotHigh(x1, y1, x2, y2);
	}
    }
}

void PixelCanvas::loadSpriteDirectory(string dirPath){
    spriteLibrary.loadDirectory("./resources/" + dirPath, ".png");
}

void PixelCanvas::loadSpriteMap(string path){
    spriteLibrary.loadItem("./resources/" + path);
}

void PixelCanvas::loadSpriteMapDirectory(string dirPath){
    loadSpriteIndex("./resources/" + dirPath);
    mapLibrary.loadDirectory("./resources/" + dirPath, ".smp");
}

void PixelCanvas::loadSprite(string path){
    spriteLibrary.loadItem("./resources/" + path);
}

void PixelCanvas::unloadAllSprites(){
    spriteLibrary.unloadAll();
}

void PixelCanvas::unloadSprite(string name){
    spriteLibrary.unloadItem(name);
}

bool PixelCanvas::loadSpriteIndex(string pathString){
    regex pat {R"(n=(\w+)\si=(\d+)\sid=(\d+))"};
    filesystem::path path{pathString};
    string dirPath = path.parent_path();
    for(auto& p : filesystem::recursive_directory_iterator(dirPath)){
	if(p.path().extension() == ".cfg"){
	    string line;
	    ifstream spriteIndexFile {p.path()};
	    if(spriteIndexFile.is_open()){
	        while(getline(spriteIndexFile, line)){
		    smatch matches;
		    if(regex_search(line, matches, pat)){
			pair<string, int> sprData = make_pair(matches[1], stoi(matches[2]));
			pair<int, pair<string,int>> data = make_pair(stoi(matches[3]), sprData);
			spriteIndex.insert(data);
		    }
		}
	    }
	}        
    }
    return false;
}

void PixelCanvas::drawFromMap(string map, int mapX, int mapY, int w, int h, int drawX, int drawY){
    shared_ptr<SpriteMap> smptr = mapLibrary.get(map);
    for(int xi = 0; xi < w; xi++){
	for(int yi = 0; yi < h; yi++){
	    pair<string, int> sprData = spriteIndex[smptr->accessMap(mapX + xi, mapY + yi)];
	    int sprWidth = smptr->getSprWidth();
	    spr(sprData.first, sprData.second, drawX + xi * sprWidth, drawY + yi * sprWidth);
	}
    }
}


Uint32 PixelCanvas::writeBufferXY(int x, int y, Uint32 data){
    if(clamp(x, 0, pixelWidth - 1) == x &&
       clamp(y, 0, pixelHeight - 1) == y){
	int i = y * pixelWidth + x;
	if(i >= 0 && i < bufferLength){
	    pixelBuffer[i] = data;
	}
    }
}


