#ifndef CLOCK_H
#define CLOCK_H

#include <chrono>

#include <SDL2/SDL.h>

namespace Defender
{
class Clock
{
public:
    Clock();
    double getTimeSpan() const;
    void tick(double desiredFrameRate);

private:
    std::chrono::high_resolution_clock::time_point t1;
    std::chrono::high_resolution_clock::time_point t2;
    double timeSpan = 0.0;
    void wait(double desiredFrameRate);
};
}

#endif // CLOCK_H
