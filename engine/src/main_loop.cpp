#include "main_loop.h"
#include "P3.h"
#include "engine.h"
#include "event_handler.h"
#include "pixel_canvas.h"
#include "loop_timer.h"
#include "game.h"
#include "app_state.h"
#include "audio_manager.h"

MainLoop::MainLoop()
    : engine{},
      audioManager{},
      pixelCanvas{engine.getRenderer(), engine.getWindow()},
      eventHandler{},
      p3{pixelCanvas, eventHandler, audioManager},
      loopTimer{60, [&](){eventFunc();}, [&](double fdt){updateFunc(fdt);}, [&](){renderFunc();}, [&](){closeFunc();}}
{
    AppState::setPixelFormat(SDL_GetWindowPixelFormat(engine.getWindow()));
}

MainLoop::~MainLoop(){
    closeFunc();
}

void MainLoop::run(){
    _init(p3);
    loopTimer.startLoop();
}

void MainLoop::eventFunc(){
    eventHandler.handleEvents();
    if(eventHandler.gotQuit()){
        loopTimer.killLoop();
    }
}

void MainLoop::updateFunc(double fdt){
    _update(p3, fdt);
    _draw(p3, fdt);
}

void MainLoop::renderFunc(){
    pixelCanvas.render();
    engine.render();
}

void MainLoop::closeFunc(){
    loopTimer.killLoop();
}

