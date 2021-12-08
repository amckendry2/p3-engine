#include "pixel_canvas.h"
#include "event_handler.h"
#include "app_state.h"
#include "P3.h"

using namespace std;

Color::Color(int r, int g, int b) : r{r}, g{g}, b{b}, a{255} {};
Color::Color(int r, int g, int b, int a) : r{r}, g{g}, b{b}, a{a} {};

P3::P3(PixelCanvas& pc,  EventHandler& eh, AudioManager& am)
    : pixelCanvas{pc},
      eventHandler{eh},
      audioManager{am}
{}

void P3::setPalette(initializer_list<Color> colors){
    palette.clear();
    for(Color c : colors){
	palette.push_back(c);
    }
}

void P3::setTransparentColor(int palIdx){
    Color c = palette[palIdx];
    pixelCanvas.setTransparentColor(c.r, c.g, c.b, c.a);
}

void P3::setTransparentColor(Color c){
    pixelCanvas.setTransparentColor(c.r, c.g, c.b, c.a);
}

void P3::setTransparentColor(int r, int g, int b, int a){
    pixelCanvas.setTransparentColor(r, g, b, a);
}

void P3::clearScreen(int palIdx){
    Color c = palette[palIdx];
    pixelCanvas.clear(c.r, c.g, c.b, c.a);
}

void P3::clearScreen(Color c){
    pixelCanvas.clear(c.r, c.g, c.b, c.a);
}

void P3::clearScreen(int r, int g, int b, int a){
    pixelCanvas.clear(r, g, b, a);
}

void P3::addShader(void(*shaderFunc)(double x, double y, Uint32 u_time, Uint8* r, Uint8* g, Uint8* b, Uint8* a)){
    pixelCanvas.addShader(shaderFunc);
}

void P3::shadeP(int x, int y, Color c){
    pixelCanvas.shadeP(x, y, c.r, c.g, c.b, c.a);
}

void P3::pset(int x, int y, int palIdx){
    Color c = palette[palIdx];
    pixelCanvas.pset(x, y, c.r, c.g, c.b, c.a);
}

void P3::pset(int x, int y, Color c){
    pixelCanvas.pset(x, y, c.r, c.g, c.b, c.a);
}

void P3::pset(int x, int y, int r, int g, int b, int a){
    pixelCanvas.pset(x, y, r, g, b, a);
}

void P3::rect(int x, int y, int w, int h, int palIdx){
    Color c = palette[palIdx];
    pixelCanvas.rect(x, y, w, h, c.r, c.g, c.b, c.a);
}

void P3::rect(int x, int y, int w, int h, Color c){
    pixelCanvas.rect(x, y, w, h, c.r, c.g, c.b, c.a);
}

void P3::rect(int x, int y, int w, int h, int r, int g, int b, int a){
    pixelCanvas.rect(x, y, w, h, r, g, b, a);
}

void P3::rectFill(int x, int y, int w, int h, int palIdx){
    Color c = palette[palIdx];
    pixelCanvas.rectFill(x, y, w, h, c.r, c.g, c.b, c.a);
}

void P3::rectFill(int x, int y, int w, int h, Color c){
    pixelCanvas.rectFill(x, y, w, h, c.r, c.g, c.b, c.a);
}

void P3::rectFill(int x, int y, int w, int h, int r, int g, int b, int a){
    pixelCanvas.rectFill(x, y, w, h, r, g, b, a);
}

void P3::circle(int x, int y, double rad, int palIdx){
    Color c = palette[palIdx];
    pixelCanvas.circle(x, y, rad, c.r, c.g, c.b, c.a);
}

void P3::circle(int x, int y, double rad, Color c){
    pixelCanvas.circle(x, y, rad, c.r, c.g, c.b, c.a);
}

void P3::circle(int x, int y, double rad, int r, int g, int b, int a){
    pixelCanvas.circle(x, y, rad, r, g, b, a);
}

void P3::circleFill(int x, int y, double rad, int palIdx){
    Color c = palette[palIdx];
    circleFill(x, y, rad, c);
}

void P3::circleFill(int x, int y, double rad, Color c){
    pixelCanvas.circleFill(x, y, rad, c.r, c.g, c.b, c.a);
}

void P3::circleFill(int x, int y, double rad, int r, int g, int b, int a){
    pixelCanvas.circleFill(x, y, rad, r, g, b, a);
}

void P3::line(int x1, int y1, int x2, int y2, int palIdx){
    Color c = palette[palIdx];
    pixelCanvas.line(x1, y1, x2, y2, c.r, c.g, c.b, c.a);
}

void P3::line(int x1, int y1, int x2, int y2, Color c){
    pixelCanvas.line(x1, y1, x2, y2, c.r, c.g, c.b, c.a);
}

void P3::line(int x1, int y1, int x2, int y2, int r, int g, int b, int a){
    pixelCanvas.line(x1, y1, x2, y2, r, g, b, a);
}

void P3::drawSprite(string spriteName, int index, int x, int y){
    pixelCanvas.spr(spriteName, index, x, y);
}

void P3::drawSprite(string spriteName, int x, int y){
    pixelCanvas.spr(spriteName, 0, x, y);
}

void P3::drawMap(string map, int mapX, int mapY, int w, int h, int drawX, int drawY){
    pixelCanvas.drawFromMap(map, mapX, mapY, w, h, drawX, drawY);
}


void P3::drawRotatedSprite(string spriteName, int index, int x, int y, double angle, bool reverse){
    pixelCanvas.rspr(spriteName, index, x, y, angle, reverse);
}

void P3::drawRotatedSprite(string spriteName, int x, int y, double angle, bool reverse){
    pixelCanvas.rspr(spriteName, 0, x, y, angle, reverse);
}


bool P3::buttonPressed(string button){
    return eventHandler.buttonPressed(button);
}

int P3::buttonHeld(string button){
    return eventHandler.buttonHeld(button);
}

bool P3::buttonDown(string button){
    return eventHandler.buttonDown(button);
}

void P3::loadSpriteDirectory(string dirPath){
    pixelCanvas.loadSpriteDirectory(dirPath);
}

void P3::loadSprite(string path){
    pixelCanvas.loadSprite(path);
}

void P3::loadSpriteMap(string path){
    pixelCanvas.loadSpriteMap(path);
}

void P3::loadSpriteMapDirectory(string path){
    pixelCanvas.loadSpriteMapDirectory(path);
}

void P3::loadSpriteIndex(string path){
    pixelCanvas.loadSpriteIndex(path);
}

void P3::unloadAllSprites(){
    pixelCanvas.unloadAllSprites();
}

void P3::unloadSprite(string name){
    pixelCanvas.unloadSprite(name);
}

void P3::loadMusicDirectory(string dirPath){
    return audioManager.loadMusicDirectory(dirPath);
}

void P3::unloadAllMusic(){
    audioManager.unloadAllMusic();
}

void P3::unloadAllSFX(){
    audioManager.unloadAllSFX();
}

void P3::unloadSFX(string name){
    audioManager.unloadSFX(name);
}

void P3::unloadMusic(string name){
    audioManager.unloadMusic(name);
}

void P3::loadSFXDirectory(string dirPath){
    return audioManager.loadSFXDirectory(dirPath);
}

void P3::playMusic(string name, int loops, int fadeMs, double positionSec){
    audioManager.playMusic(name, loops, fadeMs, positionSec);
}

void P3::resumeMusic(){
    audioManager.resumeMusic();
}

void P3::pauseMusic(){
    audioManager.pauseMusic();
}

void P3::stopMusic(int fadeMs){
    audioManager.stopMusic(fadeMs);
}

int P3::playSFX(string name, int channel, double pan, double volume, int loops){
    audioManager.playSFX(name, channel, pan, volume, loops);
}

int P3::playSFX(string name, int channel, double pan, double volume, int loops, int fadeMs, int limitMs){
    audioManager.playSFX(name, channel, pan, volume, loops, fadeMs, limitMs);
}

void P3::modifyChannel(int channel, double pan, double volume){
    audioManager.modifyChannel(channel, pan, volume);
}

void P3::pauseSFX(int channel){
    audioManager.pauseSFX(channel);
}

void P3::resumeSFX(int channel){
    audioManager.resumeSFX(channel);
}

void P3::stopSFX(int channel, int fadeMs){
    audioManager.stopSFX(channel, fadeMs);
}

int P3::getCanvasWidth(){return 128;}

int P3::getCanvasHeight(){return 128;}

int P3::getScreenWidth(){return 512;}

int P3::getScreenHeight(){return 512;}

void P3::quit(){ AppState::quitApp();}


    
