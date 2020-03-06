
#include <SFML/Graphics.hpp>

#define FRAME_SAMPLES 100

/**
 * @brief Keeps track of delta time between frames.
 *
 */
class FrameClock {
private:
    static const int size = FRAME_SAMPLES;

    sf::Clock clock;
    float frame_deltas[FRAME_SAMPLES] = {};
    int idx = 0;
    bool ready = false; // false when less than FRAME_SAMPLES frames were taken

    float* last_frame;

    float getAverage();

public:

    FrameClock() {
        clock.restart();
    }

    float delta() {
        return frame_deltas[0];
    }

    int getAverageFPS() {

        if( !ready ) {
            return 0;
        }
        else {
            return (int)(1 / delta());
        }
    }

    void addFrame();
};