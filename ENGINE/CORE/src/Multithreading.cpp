#include "../include/Multithreading.h"

namespace Engine
{
    void Thread::Create(Thread_function fn,const char *name,void *data)
    {
     thread=SDL_CreateThread(fn,name,data);
     if(thread==NULL)
        {
         LOG_ERROR("Thread","Thread creation(%s) failed: %s",name,Get_error());
         return;
        }
     status|=THREAD_STATUS_INITIALIZED;
    }

    void Thread::Wait()
    {
     if(!(status & THREAD_STATUS_INITIALIZED))
        {
         LOG_ERROR("Thread","Waiting for uninitialized thread");
         return;
        }
     SDL_WaitThread(thread,&return_value);
     status|=THREAD_STATUS_QUIT;
    }

    int Thread::Get_return_value()
    {
     return return_value;
    }

    void Mutex::Create()
    {
     mutex=SDL_CreateMutex();
     if(mutex==NULL)
        {
         LOG_ERROR("Thread","Mutex creation failed: %s",Get_error());
         return;
        }
    }

    void Mutex::Lock()
    {
     if(SDL_LockMutex(mutex)!=0)
        LOG_ERROR("Thread","Could not lock mutex: %s",Get_error());
    }

    void Mutex::Unlock()
    {
     if(SDL_UnlockMutex(mutex)!=0)
        LOG_ERROR("Thread","Could not unlock mutex: %s",Get_error());
    }

    void Mutex::Destroy()
    {
     SDL_DestroyMutex(mutex);
    }
}
