#ifndef AUDIO_MANAGER_H
#define AUDIO_MANAGER_H
#include <map>
#include <string>
#include <memory>
#include "music_track.h"
#include "sfx_track.h"
#include "resource_library.h"
using namespace std;

class AudioManager{
public:
    ~AudioManager();
    void loadMusicDirectory(string path);
    void loadSFXDirectory(string path);
    void unloadAllMusic();
    void unloadAllSFX();
    void unloadMusic(string name);
    void unloadSFX(string name);
    int playSFX(string name, int channel, double pan, double volume, int loops);
    int playSFX(string name, int channel, double pan, double volume, int loops, int fadeMs, int limitMs);
    void modifyChannel(int channel, double pan, double volume);
    void pauseSFX(int channel);
    void resumeSFX(int channel);
    void stopSFX(int channel, int fadeMs);
    void playMusic(string name, int loops, int fadeMs, double positionSec);
    void resumeMusic();
    void pauseMusic();
    void stopMusic(int fadeMs);
private:
    ResourceLibrary<MusicTrack> musicLibrary;
    ResourceLibrary<SFXTrack> sfxLibrary;
    // map<string, int> musicLibrary;
    // map<string, int> sfxLibrary;
};

#endif    

// Local Variables:
// mode: c++
// End:
