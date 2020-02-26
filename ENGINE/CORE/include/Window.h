#ifndef WINDOW_H
#define WINDOW_H

#include "Utilities.h"
#include "Surface.h"
#include "Render.h"
#include "Events.h"
#include "Controller.h"
#include "Window_attributes.h"

namespace Engine {
    class Window {
    private:
        SDL_Window *window = NULL;
        SDL_Surface *surface = NULL;
        Renderer renderer;
        Rectangle position = {0, 0, 0, 0};
        std::string title = "", icon = "";
        int flags = 0;
        bool opened = false;

        Game_Controller controller[3];

        void Set_flag(int flag);

        void Reset_flag(int flag);

        void Open_icon();

    public:
        Window() {}

        Window(std::string _title, int w, int h, int _flags = 0, int x = WINDOWPOS_CENTERED, int y = WINDOWPOS_CENTERED,
               std::string _icon = "");

        void Set_arguments(std::string _title, int w, int h, int _flags = 0, int x = WINDOWPOS_CENTERED,
                           int y = WINDOWPOS_CENTERED, std::string _icon = "");

        void Set_position(int x, int y, int w, int h);

        void Set_position(Rectangle rect);

        void Set_title(std::string _title);

        void Set_icon(std::string _icon);

        void Set_flags(int _flags);

        void Open();

        void
        Open(std::string _title, int w, int h, int _flags = 0, int x = WINDOWPOS_CENTERED, int y = WINDOWPOS_CENTERED,
             std::string _icon = "");

        void Close();

        void Reopen();

        void
        Reopen(std::string _title, int w, int h, int _flags = 0, int x = WINDOWPOS_CENTERED, int y = WINDOWPOS_CENTERED,
               std::string _icon = "");

        bool Get_keystate(const Scancode key);

        const Uint8 *Get_keystates();

        void Pump_events();

        void Init_Controllers();

        void Destroy_Controllers();

        void Update_Controllers_Events();

        Game_Controller *Get_controller(int id);

        Game_Controller *Get_controllers();

        Renderer *Get_renderer();

        Rectangle Get_position();
    };
}

#endif // WINDOW_H
