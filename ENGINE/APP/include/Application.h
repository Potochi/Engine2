#ifndef APPLICATION_H
#define APPLICATION_H

#include "../../CORE/CORE.h"

namespace Engine
{
    class Application_state;

    class Application
    {
     private:
     Window window;
     bool running;
     std::stack<Application_state*> states;

     public:
     ///Setters
     Application(std::string _title,int w,int h,int _flags=0,
                 std::string _icon="",
                 int x=WINDOWPOS_CENTERED,int y=WINDOWPOS_CENTERED):
                 window(_title,w,h,_flags,x,y,_icon),running(1) {};
     ///Getters
     Window *Get_window();
     Application_state *Get_application_state();

     ///Application environment management
     void Init();
     void Close();

     ///State management
     void Change_state(Application_state *state);
     void Push_state(Application_state *state);
     void Pop_state();

     ///Application management
     void Handle_events();
     void Update(int dt);
     void Draw();

     void Run();
     bool Is_running();
     void Quit();
    };
}

#endif // APPLICATION_H
