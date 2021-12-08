#ifndef LOOP_TIMER_H
#define LOOP_TIMER_H

#include <functional>

using namespace std;

class LoopTimer{
public:
    LoopTimer(double, function<void()>, function<void(double)>, function<void()>, function<void()>);
    void startLoop();
    void killLoop();
private:
    double framerate;
    bool running;
    function<void()> eventFunc;
    function<void(double)> updateFunc;
    function<void()> renderFunc;
    function<void()> closeFunc;
};

#endif
    
// Local Variables:
// mode: c++
// End:
