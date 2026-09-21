//
// Created by sloath on 21-Sep-26.
//

#include "include/Timer.h"

Timer::Timer() = default;

// clock actions
void Timer::Start()
{
    mStarted = true;
    mPaused = false;

    mStartTicks = SDL_GetTicksNS();
    mPausedTicks = 0;
}

void Timer::Stop()
{
    mStarted = false;
    mPaused = false;

    mStartTicks = 0;
    mPausedTicks = 0;
}

void Timer::Pause()
{
    if (mStarted and !mPaused)
    {
        mPaused = true;
        mPausedTicks = SDL_GetTicksNS() - mStartTicks;
        mStartTicks = 0;
    }
}

void Timer::Unpause()
{
    if (mStarted and mPaused)
    {
        mPaused = false;
        mStartTicks = SDL_GetTicksNS() - mPausedTicks;
        mPausedTicks = 0;
    }
}

// get timer's time
Uint64 Timer::getTicksNS() const
{
    Uint64 time{ 0 };
    if (mStarted)
    {
        if (mPaused) time = mPausedTicks;
        else time = SDL_GetTicksNS() - mStartTicks;
    }
    return time;
}