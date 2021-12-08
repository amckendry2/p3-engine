#ifndef SPRITE_SHEET_H
#define SPRITE_SHEET_H
#include "sprite.h"
#include <string>
#include <vector>
#include <memory>


using namespace std;

class SpriteSheet{
public:
    bool loadFromPath(const string path);
    shared_ptr<Sprite> operator[](int index);
    int size();
private:
    vector<Sprite> spriteVector;    
};

#endif

// Local Variables:
// mode: c++
// End:
