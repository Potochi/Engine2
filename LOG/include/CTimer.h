#ifndef CTIMER_H
#define CTIMER_H

#include <ctime>
#include <chrono>

namespace LOG
{
    class CTimer
    {
     private:
     std::chrono::steady_clock::time_point start;

     public:
     void Start();
     long long Get_time();
    };
}

#endif // CTIMER_H
