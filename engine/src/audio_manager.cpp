#include <SDL2/SDL_mixer.h>
#include <map>
#include <string>
#include <filesystem>
#include <memory>
#include <algorithm>
#include "music_track.h"
#include "sfx_track.h"
#include "resource_manager.h"
#include "audio_manager.h"
#include <iostream>
using namespace std;

AudioManager::~AudioManager(){
    unloadAllSFX();
    unloadAllMusic();
}

void AudioManager::loadSFXDirectory(string dirPath){
    sfxLibrary.loadDirectory("./resources/" + dirPath);
}

void AudioManager::unloadAllSFX(){
    sfxLibrary.unloadAll();
}

void AudioManager::unloadSFX(string name){
    sfxLibrary.unloadItem(name);
}

void AudioManager::loadMusicDirectory(string dirPath){
    musicLibrary.loadDirectory("./resources/" + dirPath);
}

void AudioManager::unloadAllMusic(){
    musicLibrary.unloadAll();
}

void AudioManager::unloadMusic(string name){
    musicLibrary.unloadItem(name);
}

int AudioManager::playSFX(string name, int channel, double pan, double volume, int loops){
    shared_ptr<SFXTrack> sfxptr = sfxLibrary.get(name);
    if(sfxptr != nullptr){
	int playedChannel = Mix_PlayChannel(channel, sfxptr->chunk, loops);
        modifyChannel(playedChannel, pan, volume);
    	return playedChannel;
    }
    return -1;
}

int AudioManager::playSFX(string name, int channel, double pan, double volume, int loops, int fadeMs, int limitMs){
    shared_ptr<SFXTrack> sfxptr = sfxLibrary.get(name);
    if(sfxptr != nullptr){
	int playedChannel = Mix_FadeInChannelTimed(channel, sfxptr->chunk, loops, fadeMs, limitMs);
        modifyChannel(playedChannel, pan, volume);
    	return playedChannel;
    }
    return -1;
}

void AudioManager::modifyChannel(int channel, double pan, double volume){
    pan = clamp(pan, -1.0, 1.0);
    volume = clamp(volume, 0.0, 1.0);
    Uint8 lowChannel = 254 * (1-abs(pan));
    Uint8 left = pan > 0 ? lowChannel : 254;
    Uint8 right = pan > 0 ? 254 : lowChannel;
    Mix_SetPanning(channel, left, right);
    Mix_Volume(channel, volume * 128);
}

void AudioManager::pauseSFX(int channel){
    Mix_Pause(channel);
}

void AudioManager::resumeSFX(int channel){
    Mix_Resume(channel);
}

void AudioManager::stopSFX(int channel, int fadeMs){
    Mix_FadeOutChannel(channel, fadeMs);
}

void AudioManager::playMusic(string name, int loops, int fadeMs, double positionSec){
    shared_ptr<MusicTrack> mptr = musicLibrary.get(name);
    Mix_FadeInMusicPos(mptr->music, loops, fadeMs, positionSec);
}

void AudioManager::resumeMusic(){
    Mix_ResumeMusic();
}

void AudioManager::pauseMusic(){
    Mix_PauseMusic();
}

void AudioManager::stopMusic(int fadeMs){
    if(Mix_PlayingMusic() == 1){
	Mix_FadeOutMusic(fadeMs);
    }
}




