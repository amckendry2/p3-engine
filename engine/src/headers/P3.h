#ifndef P3_H
#define P3_H

#include "pixel_canvas.h"
#include "event_handler.h"
#include "audio_manager.h"

#include <string>

struct Color{
    int r;
    int g;
    int b;
    int a;
    Color(int r, int g, int b);
    Color(int r, int g, int b, int a);
};

class P3 {
public:
    P3(PixelCanvas&, EventHandler&, AudioManager&);
    void setPalette(initializer_list<Color> colors);
    void setTransparentColor(int c);
    void setTransparentColor(Color c);
    void setTransparentColor(int r, int g, int b, int a = 255);
    void clearScreen(int c);
    void clearScreen(Color c);
    void clearScreen(int r, int g, int b, int a = 255);
    void addShader(void(*shaderFunc)(double x, double y, Uint32 u_time, Uint8*r,Uint8*g,Uint8*b,Uint8*a));
    void shadeP(int x, int y, Color color);
    void pset(int x, int y, int color);
    void pset(int x, int y, Color color);
    void pset(int x, int y, int r, int g, int b, int a = 255);
    void drawSprite(string spriteName, int index, int x, int y);
    void drawSprite(string spriteName, int x, int y);
    void drawMap(string map, int mapX, int mapY, int w, int h, int drawX, int drawY);
    void rect(int x, int y, int w, int h, int c);
    void rect(int x, int y, int w, int h, Color c);
    void rect(int x, int y, int w, int h, int r, int g, int b, int a = 255);
    void rectFill(int x, int y, int w, int h, int c);
    void rectFill(int x, int y, int w, int h, Color c);
    void rectFill(int x, int y, int w, int h, int r, int g, int b, int a = 255);
    void circle(int x, int y, double rad, int c);
    void circle(int x, int y, double rad, Color c);
    void circle(int x, int y, double rad, int r, int g, int b, int a = 255);
    void circleFill(int x, int y, double rad, int c);
    void circleFill(int x, int y, double rad, Color c);
    void circleFill(int x, int y, double rad, int r, int g, int b, int a = 255);
    void line(int x1, int y1, int x2, int y2, int c);
    void line(int x1, int y1, int x2, int y2, Color c);
    void line(int x1, int y1, int x2, int y2, int r, int g, int b, int a = 255);
    void drawRotatedSprite(string spriteName, int index, int x, int y, double angle, bool reverse);
    void drawRotatedSprite(string spriteName, int x, int y, double angle, bool reverse);
    bool buttonPressed(string button);
    bool buttonDown(string button);
    int buttonHeld(string button);
    int getCanvasWidth();
    int getCanvasHeight();
    int getScreenWidth();
    int getScreenHeight();
    void loadSpriteDirectory(string dirPath);
    void loadSprite(string path);
    void unloadAllSprites();
    void unloadSprite(string name);
    void loadMusicDirectory(string dirPath);
    void loadSFXDirectory(string dirPath);
    void loadSpriteMap(string path);
    void loadSpriteIndex(string path);
    void loadSpriteMapDirectory(string path);
    void unloadAllMusic();
    void unloadAllSFX();
    void unloadMusic(string name);
    void unloadSFX(string name);
    void playMusic(string name, int loops = -1, int fadeMs = 0, double positionSec = 0);
    void resumeMusic();
    void pauseMusic();
    void stopMusic(int fadeMs = 0);
    int playSFX(string name, int channel = -1, double pan = 0, double volume = 1, int loops = 0);
    int playSFX(string name, int channel, double pan, double volume, int loops, int fadeMs, int limitMs);
    void modifyChannel(int channel, double pan, double volume);
    void pauseSFX(int channel = -1);
    void resumeSFX(int channel = -1);
    void stopSFX(int channel = -1, int fadeMs = 0);
    void quit();
private:
    PixelCanvas& pixelCanvas;
    EventHandler& eventHandler;
    AudioManager& audioManager;
    vector<Color> palette;
};

#endif

// Local Variables:
// mode: c++
// End:
