#ifndef TEST_STATE_H
#define TEST_STATE_H

#include "../../ENGINE/Engine.h"


namespace Sandbox
{
    using namespace Engine;

    class Test_state : public Engine::Application_state
    {
     private:
     int countdown=100;
     ECS::Entity_handle background,player,enemies[4],text;
     std::unique_ptr<ECS::System> movement_system,rendering_system,player_movement_system;

     public:
     Test_state(Engine::Application *_application) : Application_state(_application) {}

     void Load();
     void Clear();

     void Pause();
     void Resume();

     void Handle_events();
     void Update(int dt);
     void Draw();
    };

    class Test_state2 : public Engine::Application_state
    {
     private:
     int countdown=100;
     ECS::Entity_handle background,player,enemies[4];
     std::unique_ptr<ECS::System> movement_system,rendering_system,player_movement_system;

     public:
     Test_state2(Engine::Application *_application) : Application_state(_application) {}

     void Load();
     void Clear();

     void Pause();
     void Resume();

     void Handle_events();
     void Update(int dt);
     void Draw();
    };

    class Image : public ECS::Component<Image>
    {
     public:
     Engine::Texture *img;

     Image(Engine::Texture *_img) : img(_img) {};
    };

    class Position : public ECS::Component<Position>
    {
     public:
     int x,y;
     int screenX,screenY;

     Position(int _x,int _y) : x(_x),y(_y) {};
    };

    class Movable : public ECS::Component<Movable>
    {
    };

    class Event_handler : public ECS::Component<Event_handler>
    {
    };

    class Reset_event : public EV_BUS::Event
    {
     public:
     ECS::Entity entity;

     Reset_event(ECS::Entity _ent) : entity(_ent) {}
    };

    class Movement_system : public ECS::System
    {
     public:
     Movement_system()
     {
      mask.Add_component<Position>();
      mask.Add_component<Movable>();
     }

     void On_reset_event(Reset_event *ev);

     void Update(int dt);
     void Render(){}
     void Init();
    };

    class Rendering_system : public ECS::System
    {
     public:
     Rendering_system()
     {
      mask.Add_component<Position>();
      mask.Add_component<Image>();
     }
     void Update(int dt){}
     void Render();
     void Init(){}
    };

    class Player_movement_system : public ECS::System
    {
     public:
     Player_movement_system()
     {
      mask.Add_component<Position>();
      mask.Add_component<Movable>();
      mask.Add_component<Event_handler>();
     }

     void Update(int dt);
     void Render(){}
     void Init(){}
    };
}

#endif // TEST_STATE_H
