#include "loop_timer.h"
#include "frame_ring_buffer.h"
#include <SDL2/SDL.h>
#include <iostream>
#include <functional>


LoopTimer::LoopTimer(double framerate, function<void()> ef, function<void(double)> uf, function<void()> rf, function<void()> cf)
    : running{false},
      framerate{framerate},
      eventFunc{ef},
      updateFunc{uf},
      renderFunc{rf},
      closeFunc{cf}
{}

void LoopTimer::startLoop(){
    
    if(running)
	return;
    running = true;
    
    int64_t ticks_60hz = SDL_GetPerformanceFrequency() / 60;
    int64_t snapVals[]{ticks_60hz, ticks_60hz * 2, ticks_60hz * 3, ticks_60hz * 4, (ticks_60hz+1)/2};
    
    double updateRate = framerate;
    double fixedDeltaTime = 1.0 / updateRate;
    int64_t targetFrameTime = SDL_GetPerformanceFrequency() / updateRate;
    int64_t maxDeviation = SDL_GetPerformanceFrequency() * .0002;
    
    int64_t accumulator = 0;
    int64_t prevFrameTime = SDL_GetPerformanceCounter();

    int frameCount = 0;

    FrameRingBuffer ringBuffer{4, targetFrameTime};

    while(running){

	int64_t currentFrameTime = SDL_GetPerformanceCounter();
	int64_t deltaTime = currentFrameTime - prevFrameTime;
	prevFrameTime = currentFrameTime;

	for(int64_t val : snapVals){
	    if(abs(deltaTime - val) < maxDeviation){
		deltaTime = val;
		break;
	    }	    
	}

        ringBuffer.push(deltaTime);
	deltaTime = ringBuffer.average();

	accumulator += deltaTime;

        eventFunc(); //event call

	while(accumulator >= targetFrameTime){
	    frameCount++;
	    updateFunc(fixedDeltaTime); //update call
	    accumulator -= targetFrameTime;
	}
	renderFunc(); //render call
    }
    running = false;
    closeFunc(); //quit app
    return;
}

void LoopTimer::killLoop(){running = false;}
