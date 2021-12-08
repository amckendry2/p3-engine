#ifndef FRAME_RING_BUFFER_H
#define FRAME_RING_BUFFER_H

#include <vector>
#include <cstdint>
using namespace std;

class FrameRingBuffer{
public:
    FrameRingBuffer(size_t size, int64_t value);
    void push(int64_t value);
    int64_t average();
private:
    vector<int64_t> buffer;
    size_t insertAt;
};      
#endif

// Local Variables:
// mode: c++
// End:
