#ifndef MULTITHREADING_H
#define MULTITHREADING_H

#include "Utilities.h"

namespace Engine
{
    typedef int (*Thread_function) (void *data);

    enum Thread_status
    {
     THREAD_STATUS_INVALID=         0,
     THREAD_STATUS_INITIALIZED=     1<<0,
     THREAD_STATUS_QUIT=            1<<1,
    };

    class Thread
    {
     private:
     SDL_Thread *thread;
     int return_value;
     Thread_status status=THREAD_STATUS_INVALID;

     public:
     void Create(Thread_function fn,const char *name,void *data);
     void Wait();
     int Get_return_value();
    };

    class Mutex
    {
     private:
     SDL_mutex *mutex;

     public:
     void Create();
     void Lock();
     void Unlock();
     void Destroy();
    };
}

#endif // MULTITHREADING_H
