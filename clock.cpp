#include "clock.h"

Defender::Clock::Clock() : timeSpan(0.0)
{
    this->t1 = std::chrono::high_resolution_clock::now();
    this->t2 = this->t1;
}

void Defender::Clock::tick(double desiredFrameRate = 0.0)
{
    // Get the time now
    t1 = std::chrono::high_resolution_clock::now();

    // Get the time span in seconds
    timeSpan = std::chrono::duration_cast
            <std::chrono::duration<double>>(t1 - t2).count();

    // Wait if given a framerate
    if (desiredFrameRate > 0.0)
    {
        wait(desiredFrameRate);
    }

    // Set the previous time to the current time
    // This is needed for the timespan in the next update
    t2 = t1;
}

void Defender::Clock::wait(double desiredFrameRate)
{
    // Get how long to wait for, given the frame rate
    // The total time for each update is the reciprocal of the framerate
    // The time to wait should be the total time of the update minus the time
    // take so far
    double waitTime = (1.0 / desiredFrameRate) - timeSpan;

    // Wait if we are not behind
    if (waitTime > 0)
    {
        SDL_Delay(waitTime * 1000);

        // Update the time span to account for the total update
        t1 = std::chrono::high_resolution_clock::now();
        timeSpan = std::chrono::duration_cast
                <std::chrono::duration<double>>(t1 - t2).count();
    }
}

double Defender::Clock::getTimeSpan() const
{
    // Return a fixed value if the update took too long
    // This avoids large jumps in the position updates
    if (timeSpan >= 0.2)
    {
        return 0.2;
    }
    return timeSpan;
}
