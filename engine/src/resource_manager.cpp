#include "resource_manager.h"
#include "sprite_sheet.h"
#include "music_track.h"
#include "sfx_track.h"
#include "sprite_map.h"
#include <filesystem>
#include <iostream>

using namespace std;

template <typename T> 
int ResourceManager<T>::currentId = 0;

template <typename T>
map<string, pair<int, shared_ptr<T>>> ResourceManager<T>::resources = {};

template <typename T>
int ResourceManager<T>::add(string filePath){
    auto it = resources.find(filePath);
    if(it != resources.end()){
	cout << "Tried to re-load resource at: " << filePath << endl;
    	return it->second.first;
    }
    shared_ptr<T> resource = make_shared<T>();
    if(!resource->loadFromPath(filePath)){
    	return -1;
    } 
    resources.insert(make_pair(filePath, make_pair(currentId, resource)));
    return currentId++;
};

template <typename T>
bool ResourceManager<T>::remove(int id){
    for(auto it = resources.begin(); it != resources.end(); ++it){
	if(it->second.first == id){
	    resources.erase(it->first);
	    return true;
	}
    }
    return false;
}

template <typename T>
shared_ptr<T> ResourceManager<T>::get(int id){
    for(auto it = resources.begin(); it != resources.end(); ++it){
	if(it->second.first == id)
	    return it->second.second;
    }
    return nullptr;
}

template <typename T>
bool ResourceManager<T>::has(int id){
    return get(id) != nullptr;
}

template class ResourceManager<SpriteSheet>;
template class ResourceManager<MusicTrack>;
template class ResourceManager<SFXTrack>;
template class ResourceManager<SpriteMap>;
