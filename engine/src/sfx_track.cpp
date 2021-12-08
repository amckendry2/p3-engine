#include "sfx_track.h"
#include <string>
#include <SDL2/SDL_mixer.h>

SFXTrack::SFXTrack() : chunk{nullptr}{};

SFXTrack::~SFXTrack(){
    if(chunk != nullptr)
	Mix_FreeChunk(chunk);
}

bool SFXTrack::loadFromPath(string filePath){
    chunk = Mix_LoadWAV(filePath.c_str());
    return chunk != NULL;
}
