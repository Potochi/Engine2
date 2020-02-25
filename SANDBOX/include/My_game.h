#ifndef MY_GAME_H
#define MY_GAME_H

#include "../../ENGINE/Engine.h"


namespace Mine_game
{
    using namespace Engine;

    class My_game : public Engine::Application_state
    {
     private:
     int countdown=100;
     ECS::Entity_handle background,snek,food;
     std::unique_ptr<ECS::System> movement_system,rendering_system,player_movement_system, collision_system;

     public:
     My_game(Engine::Application *_application) : Application_state(_application) {}

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
     int x, y, w, h;
     int screenX,screenY;

     Position(int _x,int _y,int _w = 0, int _h = 0) : x(_x), y(_y), w(_w), h(_h) {};
    };

    class Body : public ECS::Component<Body>
    {
    };

    class Movable : public ECS::Component<Movable>
    {
     public:
     float dx, dy;

     Movable(int _dx, int _dy) : dx(_dx), dy(_dy) {};
    };

    class Player : public ECS::Component<Player>
    {
    };

    class Food : public ECS::Component<Food>
    {
    };

    class Event_handler : public ECS::Component<Event_handler>
    {
    };

    class Food_eaten_event : public EV_BUS::Event
    {
     public:
     ECS::Entity entity;

     Food_eaten_event(ECS::Entity _ent) : entity(_ent) {}
    };

    class Movement_system : public ECS::System
    {
     public:
     Movement_system()
     {
      mask.Add_component<Position>();
      mask.Add_component<Movable>();
     }

     void Update(int dt);
     void Render(){}
     void Init() {}
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

    class Food_system : public ECS::System
    {
     public:
     Food_system()
     {
      mask.Add_component<Food>();
     }

     void On_food_eaten_event(Food_eaten_event *ev);

     void Update(int dt){}
     void Render();
     void Init();
    };

    class Player_movement_system : public ECS::System
    {
     public:
     Player_movement_system()
     {
      mask.Add_component<Position>();
      mask.Add_component<Movable>();
      mask.Add_component<Player>();
     }

     void Update(int dt);
     void Render(){}
     void Init(){}
    };

    class Collisision_detection_system : public ECS::System
    {
     public:
     Collisision_detection_system()
     {
      mask.Add_component<Position>();
      mask.Add_component<Body>();
     }

     bool Collision(Position pos1, Position pos2);

     void Update(int dt);
     void Render(){}
     void Init(){}
    };
}

#endif // MY_GAME_H
