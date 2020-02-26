#ifndef TIMER_H
#define TIMER_H

#include "../include/SDL_includes.h"

namespace Engine {
    class Timer {
    private:
        int startTicks;
        int pausedTicks;
        bool paused;
        bool started;

    public:
        Timer();

        void Start();

        void Stop();

        void Pause();

        void Unpause();

        int Get_ticks();

        bool Is_started();

        bool Is_paused();
    };
}

#endif // TIMER_H
