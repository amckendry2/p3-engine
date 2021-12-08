#ifndef RESOURCE_LIBRARY_H
#define RESOURCE_LIBRARY_H

#include <string>
#include <map>
#include <memory>
using namespace std;

template<typename T>
class ResourceLibrary{
public:
    void loadDirectory(string dirPath);
    void loadDirectory(string dirPath, string extension);
    void loadItem(string pathStr);
    void unloadAll();
    void unloadItem(string name);
    bool has(string name);
    shared_ptr<T> get(string name);
private:
    map<string, int> library;
};

#endif

// Local Variables:
// mode: c++
// End:
