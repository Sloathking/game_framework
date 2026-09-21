//
// Created by sloath on 21-Sep-26.
//

#ifndef TIMER_H
#define TIMER_H

#include <SDL3/SDL.h>

class Timer
{
public:
    Timer();

    // clock actions
    void Start();
    void Stop();
    void Pause();
    void Unpause();

    // get timer's time
    [[nodiscard]] Uint64 getTicksNS() const;

    // check status of timer
    [[nodiscard]] bool IsStarted() const {return mStarted; }
    [[nodiscard]] bool isPaused() const { return mPaused and mStarted; }

private:
    Uint64 mStartTicks{0};     // the time that the timer was started
    Uint64 mPausedTicks{0};    // the ticks stored when the time was paused

    // timer status
    bool mPaused{false};
    bool mStarted{false};

};

#endif //TIMER_H
