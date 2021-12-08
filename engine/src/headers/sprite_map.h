#ifndef SPRITE_MAP_H
#define SPRITE_MAP_H

#include <string>
#include <vector>

using namespace std;

class SpriteMap{
public:
    bool loadFromPath(const string path);
    int accessMap(int x, int y);
    int getSprWidth();
private:
    vector<int> mapVector;
    int mapWidth;
    int sprWidth;
};

#endif

// Local Variables:
// mode: c++
// End:
