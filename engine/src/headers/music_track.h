#ifndef MUSIC_TRACK_H
#define MUSIC_TRACK_H
#include <SDL2/SDL_mixer.h>
#include <string>
using namespace std;

struct MusicTrack {
    MusicTrack();
    ~MusicTrack();
    Mix_Music* music;
    bool loadFromPath(string filePath);
};

#endif

// Local Variables:
// mode: c++
// End:
