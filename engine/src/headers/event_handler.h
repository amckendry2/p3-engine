#ifndef EVENT_HANDLER_H
#define EVENT_HANDLER_H

#include <map>
#include <string>
using namespace std;

class EventHandler{
public:
    EventHandler();
    void handleEvents();
    bool buttonPressed(string button);
    bool buttonDown(string button);
    int buttonHeld(string button);
    bool gotQuit();
private:
    map<int, int> inputState;
    bool quit;
};


#endif
