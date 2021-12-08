#ifndef APP_STATE_H
#define APP_STATE_H

#include <SDL2/SDL.h>

class AppState{
public:
    static void quitApp();
    static bool didQuit();
    static void setPixelFormat(Uint32 pixelFormat);
    static Uint32 getPixelFormat();
private:
    static Uint32 pixelFormat;
    static bool quit;
};

#endif

