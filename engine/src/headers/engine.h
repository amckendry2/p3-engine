#ifndef ENGINE_H
#define ENGINE_H

#include <SDL2/SDL.h>
#include <string>

class Engine{
public:
    Engine();
    ~Engine();
    void close();
    SDL_Renderer* getRenderer();
    SDL_Window* getWindow();
    void render();
private:
    SDL_Window* appWindow;
    SDL_Renderer* appRenderer;
};

#endif
    
// Local Variables:
// mode: c++
// End:
