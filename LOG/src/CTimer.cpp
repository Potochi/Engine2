#include "../include/CTimer.h"

namespace LOG
{
    void CTimer::Start()
    {
     start=std::chrono::steady_clock::now();
    }

    long long CTimer::Get_time()
    {
     std::chrono::steady_clock::time_point end;
     end=std::chrono::steady_clock::now();
     return std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    }
}
