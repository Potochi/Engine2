#include "../include/Test_state.h"

namespace Sandbox {
    void Movement_system::Init() {
        application->Get_application_state()->Get_event_bus()->Subscribe(this, &Movement_system::On_reset_event);
    }

    void Movement_system::Update(int dt) {
        for (auto &entity:entities) {
            ECS::Component_handle<Position> pos;
            engine->Translate(entity, pos);
            pos->x += dt / 5;
            pos->y += dt / 10;

            if (pos->x >= application->Get_window()->Get_position().w - 40 ||
                pos->y >= application->Get_window()->Get_position().h - 40)
                application->Get_application_state()->Get_event_bus()->Publish(new Reset_event(entity));
        }
    }

    void Movement_system::On_reset_event(Reset_event *ev) {
        ECS::Component_handle<Position> pos;
        engine->Translate(ev->entity, pos);

        pos->x = 0;
        pos->y = 0;
    }

    void Rendering_system::Render() {
        for (auto &entity:entities) {
            ECS::Component_handle<Position> pos;
            engine->Translate(entity, pos);

            ECS::Component_handle<Image> img;
            engine->Translate(entity, img);

            //application->Get_window()->Close();
            application->Get_window()->Get_renderer()->Draw_texture(pos->x, pos->y, img->img);

            //printf("id=%d, x=%d, y=%d\n",entity.id,pos->x,pos->y);
        }
    }

    void Player_movement_system::Update(int dt) {
        for (auto &entity:entities) {
            if (application->Get_window()->Get_keystate(SCANCODE_SPACE))
                application->Get_application_state()->Get_event_bus()->Publish(new Reset_event(entity));
            if (application->Get_window()->Get_keystate(SCANCODE_ESCAPE)) {
                application->Quit();
                break;
            }
        }
        if (application->Get_window()->Get_keystate(SCANCODE_BACKSPACE)) {
            application->Pop_state();
            Delay(500);
        }
        if (application->Get_window()->Get_keystate(SCANCODE_RETURN)) {
            application->Push_state(new Test_state2(application));
            Delay(500);
        }
    }

    ///**************************************************************************

    void Test_state::Load() {
        movement_system = make_unique<Movement_system>();
        engine->Add_system(std::move(movement_system));
        rendering_system = make_unique<Rendering_system>();
        engine->Add_system(std::move(rendering_system));
        player_movement_system = make_unique<Player_movement_system>();
        engine->Add_system(std::move(player_movement_system));

        background = engine->Add_entity();
        background.Add_component(Image(resource_manager.Get<Texture>("res/img.png")));
        background.Add_component(Position(45, 33));

        text = engine->Add_entity();
        Color text_color(255, 0, 0, 255);
        text.Add_component(
                Image(RENDERER->Create_TTF_texture(resource_manager.Get<Font>("res/font.ttf"), "TEST", text_color)));
        text.Add_component(Position(125, 40));
        text.Add_component(Movable());

        player = engine->Add_entity();
        player.Add_component(Image(resource_manager.Get<Texture>("res/sq.png")));
        player.Add_component(Position(0, 0));
        player.Add_component(Movable());
        player.Add_component(Event_handler());

        for (int i = 0; i < 4; i++) {
            enemies[i] = engine->Add_entity();
            enemies[i].Add_component(Image(resource_manager.Get<Texture>("res/sq2.png")));
            enemies[i].Add_component(Position(i * 40, i * 50));
            enemies[i].Add_component(Movable());
        }

        engine->Init();
    }

    void Test_state::Clear() {
        resource_manager.Clear<Texture>();
    }

    void Test_state::Pause() {
    }

    void Test_state::Resume() {
    }

    void Test_state::Handle_events() {
    }

    void Test_state::Update(int dt) {
        engine->Update(dt);
    }

    void Test_state::Draw() {
        application->Get_window()->Get_renderer()->Flush();
        engine->Render();
        application->Get_window()->Get_renderer()->Present();
    }

    ///******************************************************\

    void Test_state2::Load() {
        movement_system = make_unique<Movement_system>();
        engine->Add_system(std::move(movement_system));
        rendering_system = make_unique<Rendering_system>();
        engine->Add_system(std::move(rendering_system));
        player_movement_system = make_unique<Player_movement_system>();
        engine->Add_system(std::move(player_movement_system));

        background = engine->Add_entity();
        background.Add_component(Image(resource_manager.Get<Texture>("res/img.png")));
        background.Add_component(Position(45, 33));

        player = engine->Add_entity();
        player.Add_component(Image(resource_manager.Get<Texture>("res/sq.png")));
        player.Add_component(Position(0, 0));
        player.Add_component(Movable());

        for (int i = 0; i < 4; i++) {
            enemies[i] = engine->Add_entity();
            enemies[i].Add_component(Image(resource_manager.Get<Texture>("res/sq2.png")));
            enemies[i].Add_component(Position(i * 40, i * 50));
            enemies[i].Add_component(Movable());
            enemies[i].Add_component(Event_handler());
        }

        engine->Init();
    }

    void Test_state2::Clear() {
        resource_manager.Clear<Texture>();
    }

    void Test_state2::Pause() {
    }

    void Test_state2::Resume() {
    }

    void Test_state2::Handle_events() {
    }

    void Test_state2::Update(int dt) {
        engine->Update(dt);
    }

    void Test_state2::Draw() {
        application->Get_window()->Get_renderer()->Flush();
        engine->Render();
        application->Get_window()->Get_renderer()->Present();
    }
}
