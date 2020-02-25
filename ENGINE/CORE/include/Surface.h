#ifndef SURFACE_H
#define SURFACE_H

#include "Utilities.h"

namespace Engine
{
    class Surface
    {
     private:
     int w=0,h=0;
     SDL_Surface *image=NULL;

     public:
     Surface();
     Surface(SDL_Surface *_surf);
     Surface(int _w,int _h,SDL_Surface *_image);
     int Get_w();
     int Get_h();
     SDL_Surface *Get_image();
     void Clear();
    };
}

#endif // SURFACE_H
