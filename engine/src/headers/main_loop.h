#ifndef MAIN_LOOP_H
#define MAIN_LOOP_H

#include "P3.h"
#include "engine.h"
#include "event_handler.h"
#include "pixel_canvas.h"
#include "loop_timer.h"
#include "audio_manager.h"

class MainLoop{
public:
    MainLoop();
    ~MainLoop();
    void run();
private:
    void updateFunc(double fdt);
    void eventFunc();
    void renderFunc();
    void closeFunc();
    P3 p3;
    Engine engine;
    EventHandler eventHandler;
    PixelCanvas pixelCanvas;
    LoopTimer loopTimer;
    AudioManager audioManager;
};

#endif

// Local Variables:
// mode: c++
// End:
