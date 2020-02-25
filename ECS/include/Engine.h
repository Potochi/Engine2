#ifndef ECS_ENGINE_H
#define ECS_ENGINE_H

#include "Component.h"
#include "Component_handle.h"
#include "Component_manager.h"
#include "Component_mask.h"
#include "Entity.h"
#include "Entity_manager.h"
#include "System.h"

namespace ECS
{
    class Entity_handle;

    class Engine
    {
     private:
     std::vector<std::unique_ptr<Base_component_manager>> component_managers;
     std::vector<std::unique_ptr<System>> systems;
     std::unique_ptr<Entity_manager> entity_manager;
     std::map<Entity,Component_mask> entity_masks;
     ENGINE_APP *application;

     public:
     explicit Engine(std::unique_ptr<Entity_manager> _entity_manager);
     void Set_application(ENGINE_APP *_application);

     void Init();
     void Update(int dt);
     void Render();

     void Add_system(std::unique_ptr<System> system);

     Entity_handle Add_entity();
     void Remove_entity(Entity entity);

     void Update_entity_mask(Entity const &entity,Component_mask old_mask);

     template <typename Component_type>
     Component_manager<Component_type> *Get_component_manager()
     {
      int type_id=Get_component_type_id<Component_type>();
      if(type_id>=component_managers.size() || component_managers[type_id]==0)
         Add_component_manager(make_unique<Component_manager<Component_type>>());
      return static_cast<Component_manager<Component_type>*>(component_managers[type_id].get());
     }


     template <typename Component_type>
     void Add_component_manager(std::unique_ptr<Component_manager<Component_type>> manager)
     {
      int type_id=Get_component_type_id<Component_type>();
      if(type_id>=component_managers.size())
         component_managers.resize(type_id+1);
      if(component_managers[type_id]==0)
         component_managers[type_id]=std::move(manager);

      LOG_INFO("ECS","Added new Component_manager for %s with id=%d",UTIL::Get_type<Component_type>(),type_id);
     }

     template <typename Component_type>
     void Add_component(Entity &entity,Component_type &&component)
     {
      Component_manager<Component_type> *manager=Get_component_manager<Component_type>();
      manager->Add_component(entity,component);

      Component_mask old_mask=entity_masks[entity];
      entity_masks[entity].Add_component<Component_type>();

      Update_entity_mask(entity,old_mask);

      //LOG_INFO("ECS","Added new component %s to entity %d",UTIL::Get_type<Component_type>(),entity.id);
     }

     template <typename Component_type>
     void Remove_component(Entity const &entity)
     {
      Component_manager<Component_type> *manager=Get_component_manager<Component_type>();
      Component_type component=manager->Find(entity);
      component.Clear();

      Component_mask old_mask=entity_masks[entity];
      entity_masks[entity].Remove_component<Component_type>();

      Update_entity_mask(entity,old_mask);
     }

     template <typename Component_type>
     void Translate(Entity entity,Component_handle<Component_type> &handle)
     {
      Component_manager<Component_type> *manager=Get_component_manager<Component_type>();
      handle=Component_handle<Component_type>(entity,manager->Find(entity),manager);
     }

    };
}

#endif // ECS_ENGINE_H
