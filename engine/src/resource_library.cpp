#include "resource_library.h"
#include "resource_manager.h"
#include "sprite_sheet.h"
#include "music_track.h"
#include "sfx_track.h"
#include "sprite_map.h"
#include <filesystem>
#include <memory>
#include <string>
#include <map>
#include <iostream>
using namespace std;

template<typename T>
void ResourceLibrary<T>::loadDirectory(string dirPath){
    for(auto& p : filesystem::directory_iterator(dirPath))
	loadItem(p.path());
}

template<typename T>
void ResourceLibrary<T>::loadDirectory(string dirPath, string extension){
    for(auto& p : filesystem::directory_iterator(dirPath)){
	if(p.path().extension() == extension){
	    loadItem(p.path());
	}
    }
}

template<typename T>
void ResourceLibrary<T>::loadItem(string pathStr){
    filesystem::path path = pathStr;
    string name = path.filename().replace_extension("");
    if(library.contains(name)){
	cout << "Tried to load duplicate filename: " << name << endl;
	return;
    }
    int id = ResourceManager<T>::add(path);
    if(id != -1){	
	library.insert(make_pair(name, id));
	cout << "Loaded: " << path << " as: " << '"' + name + '"' << endl;
    } else {
	cout << "Failed to load: " << path << endl;
    }
}

template<typename T>
void ResourceLibrary<T>::unloadAll(){
    if(library.size() > 0){
	for(auto item : library){
	    cout << "Unloading resource: " << item.first;
	    bool res = ResourceManager<T>::remove(item.second);
	    if(res)
		cout << " ...succeeded" << endl;
	    else cout << " ...failed" << endl;
	}
	library.clear();
    }
}

template<typename T>
void ResourceLibrary<T>::unloadItem(string name){
    if(!library.contains(name)){
	cout << "Couldn't find resource to unload: " + name << endl;
	return;
    }
    cout << "Unloading resource: " << name;
    bool res = ResourceManager<T>::remove(library[name]);
    if(res){
	cout << " ...succeeded" << endl;
    } else {
	cout << " ...failed" << endl;
    }
    library.erase(name);
}

template<typename T>
bool ResourceLibrary<T>::has(string name){
    return library.contains(name);
}

template<typename T>
shared_ptr<T> ResourceLibrary<T>::get(string name){
    if(!has(name)){
	cout << "Couldn't find resource: " << name << endl;
	return nullptr;
    }
    return ResourceManager<T>::get(library[name]);   
}

template class ResourceLibrary<SpriteSheet>;
template class ResourceLibrary<MusicTrack>;
template class ResourceLibrary<SFXTrack>;
template class ResourceLibrary<SpriteMap>;
