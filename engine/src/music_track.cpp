#include "music_track.h"
#include <string>
#include <SDL2/SDL_mixer.h>

MusicTrack::MusicTrack() : music{nullptr}{};

MusicTrack::~MusicTrack(){
    if(music != nullptr)
	Mix_FreeMusic(music);
}

bool MusicTrack::loadFromPath(string filePath){
    music = Mix_LoadMUS(filePath.c_str());
    return music != NULL;
}
