#include "../../APP/include/Application.h"
#include "../../APP/include/Application_state.h"

namespace Engine
{
    Window *Application::Get_window()
    {
     return &window;
    }

    Application_state *Application::Get_application_state()
    {
     return states.top();
    }

    void Application::Init()
    {
     Engine::Init();
     window.Open();
    }

    void Application::Close()
    {
     while(!states.empty())
           {
            states.top()->Clear();
            states.pop();
           }

     window.Close();
     Engine::Close();
    }

    void Application::Change_state(Application_state *state)
    {
     if(!states.empty())
        {
         states.top()->Clear();
         states.pop();
        }
     states.push(state);
     states.top()->Set_application(this);
     states.top()->Load();

     LOG_INFO("Application","Changed state");
    }

    void Application::Push_state(Application_state *state)
    {
     if(!states.empty())
        {
         states.top()->Pause();
        }
     states.push(state);
     states.top()->Set_application(this);
     states.top()->Load();

     LOG_INFO("Application","Pushed state");
    }

    void Application::Pop_state()
    {
     if(states.size()>1)
        {
         states.top()->Clear();
         states.pop();
        }
     else
        {
         Quit();
         return;
        }
     if(!states.empty())
        {
         states.top()->Resume();
        }
     else
        Quit();
     LOG_INFO("Application","State popped");
    }

    void Application::Handle_events()
    {
     states.top()->Handle_events();
    }

    void Application::Update(int dt)
    {
     states.top()->Update(dt);
    }

    void Application::Draw()
    {
     states.top()->Draw();
    }

    void Application::Run()
    {
     if(!states.empty())
        {
         running=true;
         Timer frame_duration;
         while(Is_running())
               {
                window.Pump_events();
                int dt=frame_duration.Get_ticks();
                Update(dt);
                //LOG_INFO("Application","Frame duration: %d",dt);

                frame_duration.Start();
                Draw();
                Delay(20);
               }
        }
     else
        {
         LOG_CRITICAL("Application","Empty Application_state stack");
        }
    }

    bool Application::Is_running()
    {
     return running;
    }

    void Application::Quit()
    {
     LOG_INFO("Application","Quit");
     running=false;
    }
}
