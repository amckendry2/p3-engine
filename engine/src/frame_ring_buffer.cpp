#include "frame_ring_buffer.h"
#include <vector>
#include <cstdint>
using namespace std;

FrameRingBuffer::FrameRingBuffer(size_t sz, int64_t val)
    : insertAt{0},
      buffer(sz, val)
{}

void FrameRingBuffer::push(int64_t val){
    buffer[insertAt] = val;
    insertAt = (insertAt + 1) % buffer.size();
}

int64_t FrameRingBuffer::average(){
    int64_t total = 0;
    for(size_t i = 0; i < buffer.size(); i++){
	total += buffer[i];
    }
    return total / buffer.size();
}

