#include "sprite_sheet.h"
#include "app_state.h"
#include <iostream>
#include <regex>
#include <fstream>
#include <filesystem>
#include <SDL2/SDL_image.h>

int SpriteSheet::size(){
    return spriteVector.size();
}

bool SpriteSheet::loadFromPath(const string pathstring){
    spriteVector.clear();
    Uint32 mappingFormat = AppState::getPixelFormat();
    regex wPat {R"(w=([\d+]))"};
    regex hPat {R"(h=([\d+]))"};
    regex nPat {R"(n=([\d+]))"};
    filesystem::path path = pathstring;
    if(path.extension() != ".png"){
    	return false;
    }
    filesystem::path cfgPath = path;
    cfgPath.replace_extension("cfg");
    ifstream cfgFile;
    string line;
    cfgFile.open(cfgPath);
    if(cfgFile.is_open()){
    	int sprWidth = NULL;
    	int sprHeight = NULL;
	int numSprites = NULL;
    	while(getline(cfgFile, line)){
    	    smatch matches;
    	    if(regex_search(line, matches, wPat)){
    		sprWidth = stoi(matches[1]);
    	    } else if(regex_search(line, matches, hPat)){
    		sprHeight = stoi(matches[1]);
    	    } else if(regex_search(line, matches, nPat)){
		numSprites = stoi(matches[1]);
	    }
    	}
    	if(sprWidth != NULL && sprHeight != NULL && numSprites != NULL){
    	    SDL_Surface* imgSurface = IMG_Load(path.c_str());
	    if(imgSurface == nullptr)
		return false;
    	    SDL_Surface* sprSurface = SDL_CreateRGBSurface(0, sprWidth, sprHeight, 32, 0, 0, 0, 0);
	    int sprite_i = 0;
    	    for(int x = 0; sprite_i < numSprites, x < imgSurface->w; x+=sprWidth){
    	    	for(int y = 0; sprite_i < numSprites, y < imgSurface->h; y+=sprHeight, sprite_i++){
    	    	    SDL_Rect frame = {x, y, sprWidth, sprHeight};
    	    	    SDL_BlitSurface(imgSurface, &frame, sprSurface, NULL);
    	    	    Sprite spr(sprSurface, mappingFormat);
    	    	    spriteVector.push_back(move(spr));
    	    	}
    	    }
    	    SDL_FreeSurface(imgSurface);
    	    SDL_FreeSurface(sprSurface);
    	    return true;
    	}
    } else {
	cout << "no .cfg file for: " << pathstring << endl;
    }
    return false;
}


shared_ptr<Sprite> SpriteSheet::operator[](int index){
    if(index > spriteVector.size() || index < 0){
	cout << "Sprite index out of bounds! Returning sprite at [0]." << endl;
	return make_shared<Sprite>();
    }
    return make_shared<Sprite>(spriteVector[index]);
}
