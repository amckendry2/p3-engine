#include "sprite_map.h"

#include <string>
#include <vector>
#include <regex>
#include <fstream>
#include <filesystem>
#include <iostream>

using namespace std;

bool SpriteMap::loadFromPath(string pathString){
    mapVector.clear();
    regex wPat {R"(w=(\d+),?\s*sw=(\d+))"};
    regex sPat {R"((\d+),?\s*)"};
    ifstream spriteMapFile{pathString};
    if(spriteMapFile.is_open()){
	string line;
	while(getline(spriteMapFile,line)){
	    smatch matches;
	    if(regex_search(line, matches, wPat)){
		mapWidth = stoi(matches[1]);
		sprWidth = stoi(matches[2]);
	    } else {
		while(regex_search(line, matches, sPat)){
		    mapVector.push_back(stoi(matches[1]));
		    line = matches.suffix().str();
		}
	    }   
	}
    }
    return mapVector.size() > 0;
}

int SpriteMap::accessMap(int x, int y){
    return mapVector[y * mapWidth + x];
}

int SpriteMap::getSprWidth(){
    return sprWidth;
}
