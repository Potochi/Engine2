#ifndef APPLICATION_STATE_H
#define APPLICATION_STATE_H

#include "../../../ECS/ECS.h"
#include "../../../RES_MANAGER/RES_MANAGER.h"
#include "../../../EV_BUS/EV_BUS.h"

namespace Engine
{
    class Application;

    class Application_state
    {
     public:
     virtual void Load()=0;
     virtual void Clear()=0;

     virtual void Pause()=0;
     virtual void Resume()=0;

     virtual void Handle_events()=0;
     virtual void Update(int dt)=0;
     virtual void Draw()=0;

     protected:
     std::unique_ptr<ECS::Engine> engine;
     RES_MANAGER::Centralized_resource_manager resource_manager;
     EV_BUS::Event_bus event_bus;
     Application *application;

     public:
     Application_state(Application *_application)
     {
      Set_application(_application);
      auto entity_manager=make_unique<ECS::Entity_manager>();
      engine=make_unique<ECS::Engine>(std::move(entity_manager));
      engine->Set_application(application);
      resource_manager.Set<Texture>(Load_texture,Clear_texture);
      resource_manager.Set<Font>(Load_font,Clear_font);
     }

     void Set_application(Application *_application)
     {
      application=_application;
     }

     Application *Get_application()
     {
      return application;
     }

     EV_BUS::Event_bus *Get_event_bus()
     {
      return &event_bus;
     }
    };
}

#endif // APPLICATION_STATE
