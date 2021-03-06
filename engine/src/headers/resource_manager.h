#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include <SDL2/SDL.h>

#include <map>
#include <memory>
#include <string>

using namespace std;

template<typename T>
class ResourceManager{
public:
    static int add(string filePath);
    static bool remove(int id);
    static shared_ptr<T> get(int id);
    static bool has(int id);
private:
    static int currentId;
    static map<string, pair<int, shared_ptr<T>>> resources;
};

#endif
// Local Variables:
// mode: c++
// End:
