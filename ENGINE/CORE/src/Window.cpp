#include "../../CORE/include/Window.h"

namespace Engine
{
    namespace Window_utilities
    {
        Window::Window(std::string _title,int w,int h,int _flags,int x,int y,std::string _icon)
        {
         Set_arguments(_title,w,h,_flags,x,y,_icon);
        }

        void Window::Set_arguments(std::string _title,int w,int h,int _flags,int x,int y,std::string _icon)
        {
         title=_title;
         position=Rectangle(x,y,w,h);
         flags=_flags;
         icon=_icon;
        }

        void Window::Set_position(int x,int y,int w,int h)
        {
         position=Rectangle(x,y,w,h);
        }

        void Window::Set_position(Rectangle rect)
        {
         position=rect;
        }

        void Window::Set_title(std::string _title)
        {
         title=_title;
        }

        void Window::Set_icon(std::string _icon)
        {
         icon=_icon;
        }

        void Window::Set_flags(int _flags)
        {
         flags=_flags;
        }

        void Window::Set_flag(int flag)
        {
         flags|=flag;
        }

        void Window::Reset_flag(int flag)
        {
         flags&=~flag;
        }


        void Window::Open_icon()
        {
         if(icon.empty())
            {
             LOG_WARNING("Window","Could not set icon: path is NULL");
             return;
            }
         Uint32 colorkey;
         SDL_Surface *icon_image=NULL;
         icon_image=IMG_Load(icon.c_str());
         if(icon_image==NULL)
            {
             LOG_WARNING("Window","Could not load icon: %s",Get_error(),NULL);
             return;
            }
         colorkey=SDL_MapRGB(icon_image->format,255,0,255);
         SDL_SetColorKey(icon_image,SDL_TRUE,colorkey);
         SDL_SetWindowIcon(window,icon_image);
         SDL_FreeSurface(icon_image);
         LOG_INFO("Window","Loaded icon: name=[%s]",icon.c_str());
        }

        void Window::Open()
        {
         if(opened)
            {
             LOG_ERROR("Window","Could not create window because there is already one opened");
             return;
            }
         window=SDL_CreateWindow(title.c_str(),position.x,position.y,position.w,position.h,flags);
         if(window==NULL)
            {
             LOG_CRITICAL("Window","Could not create window: %s",Get_error());
             exit(-1);
             return;
            }
         opened=true;
         Open_icon();
         surface=SDL_GetWindowSurface(window);
         if(SDL_GetWindowSurface(window)==NULL)
            {
             LOG_CRITICAL("Window","Could not get window surface: %s",Get_error());
             exit(-1);
            }

         LOG_INFO("Window","Window opened!");

         renderer.Open(window,SDL_RENDERER_ACCELERATED,surface->format);
         Set_global_renderer(&renderer);

         Init_Controllers();
        }

        void Window::Open(std::string _title,int w,int h,int _flags,int x,int y,std::string _icon)
        {
         Set_arguments(_title,w,h,_flags,x,y,_icon);
         Open();
        }

        void Window::Close()
        {
         if(!opened)
            {
             LOG_ERROR("Window","Could not close window because it is already closed");
             return;
            }
         SDL_DestroyWindow(window);
         opened=false;
         surface=NULL;
         renderer.Close();
         Set_global_renderer(nullptr);
         LOG_INFO("Window","Window closed");

         Destroy_Controllers();
        }

        void Window::Reopen()
        {
         Close();
         Open();
        }

        void Window::Reopen(std::string _title,int w,int h,int _flags,int x,int y,std::string _icon)
        {
         Close();
         Set_arguments(_title,w,h,_flags,x,y,_icon);
         Open();
        }

        bool Window::Get_keystate(const Scancode key)
        {
         return Events::keystates[key];
        }

        const Uint8 *Window::Get_keystates()
        {
         return Events::keystates;
        }

        void Window::Pump_events()
        {
         Events::Pump_events();
         Update_Controllers_Events();
        }

        void Window::Init_Controllers()
        {
         int number_of_controllers=SDL_NumJoysticks();
         /*if(number_of_controllers<=1)
            {
             Controller::controller_scheme=Controller::CONTROLLER_SCHEME_KEYBOARD;
             return;
            }*/
         Game_Controller::controller_scheme=CONTROLLER_SCHEME_CONTROLLERS;
         for(int i=0;i<2 && i<number_of_controllers;i++)
             {
              controller[i+1].Init(i);
             }
        }

        void Window::Destroy_Controllers()
        {
         int number_of_controllers=SDL_NumJoysticks();
         if(number_of_controllers<1)
            return;
         for(int i=0;i<2 && i<number_of_controllers;i++)
             {
              controller[i].Destroy();
             }
        }

        void Window::Update_Controllers_Events()
        {
         SDL_JoystickUpdate();
         for(int i=0;i<2;i++)
             {
              controller[i+1].Update_Events();
             }
        }

        Game_Controller *Window::Get_controller(int id)
        {
         return &controller[id+1];
        }

        Game_Controller *Window::Get_controllers()
        {
         /*Controller::Game_Controller *ctrls[3];
         for(int i=0;i<3;i++)
             ctrls[i]=&controller[i];*/
         return controller;
        }

        Renderer *Window::Get_renderer()
        {
         return &renderer;
        }

        Rectangle Window::Get_position()
        {
         return position;
        }

        /*Surface *Window::Load(std::string path_to_image)
        {
         Surface *image;
         image=surface_factory->Load(path_to_image);
         return image;
        }

        void Window::Draw(int x,int y,Surface *source)
        {
         SDL_Rect *offset;
         offset=new SDL_Rect;
         offset->x=x;
         offset->y=y;
         SDL_BlitSurface(source->Get_image(),NULL,surface,offset);
         delete offset;
         SDL_UpdateWindowSurface(window);
        }*/
    }
}
