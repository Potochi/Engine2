#include "../include/My_game.h"

namespace Mine_game
{
    void Movement_system::Update(int dt)
    {
     for(auto &entity:entities)
         {
          ECS::Component_handle<Position> pos;
          ECS::Component_handle<Movable> mov;
          engine->Translate(entity,pos);
          engine->Translate(entity,mov);
          pos->x += mov->dx * dt;
          pos->y += mov->dy * dt;

          mov->dx = mov->dy = 0;
         }
    }

    void Rendering_system::Render()
    {
     for(auto &entity:entities)
         {
          ECS::Component_handle<Position> pos;
          engine->Translate(entity,pos);

          ECS::Component_handle<Image> img;
          engine->Translate(entity,img);

          //application->Get_window()->Close();
          application->Get_window()->Get_renderer()->Draw_texture(pos->x,pos->y,img->img);

          //printf("id=%d, x=%d, y=%d\n",entity.id,pos->x,pos->y);
         }
    }

    void Food_system::Init()
    {
     application->Get_application_state()->Get_event_bus()->Subscribe(this,&Food_system::On_food_eaten_event);
    }

    void Food_system::On_food_eaten_event(Food_eaten_event *ev)
    {
     ECS::Component_handle<Position> pos;
     engine->Translate(ev->entity,pos);

     pos->x=rand() % 40;
     pos->y=rand() % 40;
    }

    void Player_movement_system::Update(int dt)
    {
     for(auto &entity:entities)
         {
          ECS::Component_handle<Position> pos;
          engine->Translate(entity,pos);
          ECS::Component_handle<Movable> mov;
          engine->Translate(entity,mov);

          if(application->Get_window()->Get_keystate(SCANCODE_UP))
             {
              mov->dy = -1.0;
             }
          if(application->Get_window()->Get_keystate(SCANCODE_DOWN))
             {
              mov->dy = +1.0;
             }
          if(application->Get_window()->Get_keystate(SCANCODE_LEFT))
             {
              mov->dx = -1.0;
             }
          if(application->Get_window()->Get_keystate(SCANCODE_RIGHT))
             {
              mov->dx = +1.0;
             }

          if(application->Get_window()->Get_keystate(SCANCODE_ESCAPE))
             {
              application->Quit();
              break;
             }
         }
    }

    bool Collisision_detection_system::Collision(Position pos1, Position pos2)
    {
     return ((pos2.x<=pos1.x+pos1.w) && (pos2.y<=pos1.y+pos1.h))&&((pos1.x<=pos2.x+pos2.w) && (pos1.y<=pos2.y+pos2.h));
    }

    void Collisision_detection_system::Update(int dt)
    {
     for(int i = 0; i < entities.size(); i++)
         {
          ECS::Component_handle<Position> pos1;
          engine->Translate(entities[i],pos1);

          for(int j = i + 1; j < entities.size(); j++)
              {
               ECS::Component_handle<Position> pos2;
               engine->Translate(entities[j],pos2);
               Position p1 = *pos1.component;
               Position p2 = *pos2.component;
               ECS::Component_handle<Player> sq;
               engine->Translate(entities[i], sq);
               ECS::Component_handle<Player> sqq;
               engine->Translate(entities[j], sqq);

               if(Collision(p1, p2))
                  {
                   LOG_CRITICAL("Debug", "Collision detected!");
                   LOG_ERROR("Debug", "sq = %p", sq);
                   LOG_ERROR("Debug", "sqq = %p", sqq);
                  }
              }
         }
    }

    ///**************************************************************************

    void My_game::Load()
    {
     movement_system=make_unique<Movement_system>();
     engine->Add_system(std::move(movement_system));
     rendering_system=make_unique<Rendering_system>();
     engine->Add_system(std::move(rendering_system));
     player_movement_system = make_unique<Player_movement_system>();
     engine->Add_system(std::move(player_movement_system));
     collision_system = make_unique<Collisision_detection_system>();
     engine->Add_system(std::move(collision_system));

     background=engine->Add_entity();
     background.Add_component(Image(resource_manager.Get<Texture>("res/background.png")));
     background.Add_component(Position(0,0));

     food = engine->Add_entity();
     food.Add_component(Image(resource_manager.Get<Texture>("res/food.png")));
     food.Add_component(Position(5, 5, 10, 10));
     food.Add_component(Body());

     snek = engine->Add_entity();
     snek.Add_component(Image(resource_manager.Get<Texture>("res/snek.png")));
     snek.Add_component(Position(0, 0, 40, 40));
     snek.Add_component(Movable(0, 0));
     snek.Add_component(Player());
     snek.Add_component(Body());

     /*player=engine->Add_entity();
     player.Add_component(Image(resource_manager.Get<Texture>("res/sq.png")));
     player.Add_component(Position(0,0));
     player.Add_component(Movable());
     player.Add_component(Event_handler());*/
     engine->Init();
    }

    void My_game::Clear()
    {
     resource_manager.Clear<Texture>();
    }

    void My_game::Pause()
    {
    }

    void My_game::Resume()
    {
    }

    void My_game::Handle_events()
    {
    }

    void My_game::Update(int dt)
    {
     engine->Update(dt);
    }

    void My_game::Draw()
    {
     application->Get_window()->Get_renderer()->Flush();
     engine->Render();
     application->Get_window()->Get_renderer()->Present();
    }
}

