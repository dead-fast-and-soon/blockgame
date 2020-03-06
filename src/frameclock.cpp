
#include "frameclock.h"


float FrameClock::getAverage() {

    float deltas = 0;
    for(int i = 0; i < size; i++) {
        deltas += frame_deltas[i];
    }
    return deltas / size;
}

void FrameClock::addFrame() {

    float delta_time = clock.getElapsedTime().asSeconds();

    if( idx == size - 1 ) ready = true;

    frame_deltas[idx] = delta_time;  // update delta at this index
    idx = (idx + 1) % size; // increment index or wrap around to 0

    clock.restart();
}