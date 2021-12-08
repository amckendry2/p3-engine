#ifndef SFX_TRACK_H
#define SFX_TRACK_H
#include <SDL2/SDL_mixer.h>
#include <string>
using namespace std;

struct SFXTrack{
    SFXTrack();
    ~SFXTrack();
    Mix_Chunk* chunk;
    bool loadFromPath(string filePath);
};

#endif

// Local Variables:
// mode: c++
// End:
