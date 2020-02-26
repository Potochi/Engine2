#include "../include/Engine.h"
#include "../include/Entity_handle.h"
#include "../../LOG/LOG.h"
#include "../../UTIL/UTIL.h"

namespace ECS {
    Engine::Engine(std::unique_ptr<Entity_manager> _entity_manager) : entity_manager(std::move(_entity_manager)) {}

    void Engine::Set_application(ENGINE_APP *_application) {
        application = _application;
    }

    void Engine::Init() {
        for (int i = 0; i < systems.size(); i++)
            systems[i]->Init();
    }

    void Engine::Update(int dt) {
        for (int i = 0; i < systems.size(); i++)
            systems[i]->Update(dt);
    }

    void Engine::Render() {
        for (int i = 0; i < systems.size(); i++)
            systems[i]->Render();
    }

    void Engine::Add_system(std::unique_ptr<System> system) {
        system->Register_engine(this);
        system->Register_application(application);
        systems.push_back(std::move(system));
//TODO aci se poate modifica
        LOG_INFO("ECS", "Added new System");
    }

    Entity_handle Engine::Add_entity() {
        LOG_INFO("ECS", "Added new Entity");
        Entity_handle handle(entity_manager->Add_entity(), this);
        return handle;
    }

    void Engine::Remove_entity(Entity entity) {
        for (int i = 0; i < systems.size(); i++)
            systems[i]->Unregister_entity(entity);

        entity_manager->Remove_entity(entity);
    }

    void Engine::Update_entity_mask(Entity const &entity, Component_mask old_mask) {
        Component_mask new_mask = entity_masks[entity];

        for (int i = 0; i < systems.size(); i++) {
            Component_mask system_mask = systems[i]->Get_mask();
            if (new_mask.Is_new_match(old_mask, system_mask)) {
                systems[i]->Register_entity(entity);
            } else if (new_mask.Is_no_longer_matching(old_mask, system_mask)) {
                systems[i]->Unregister_entity(entity);
            }
        }
    }
}
