#ifndef WRAPPERS_H
#define WRAPPERS_H

#include "Utilities.h"
#include <cstdio>

namespace Engine
{
    class Rectangle
    {
     public:
     int x=0,y=0,w=0,h=0;

     Rectangle();
     Rectangle(int _x,int _y,int _w,int _h);
     Rectangle(int _x,int _y);
     Rectangle(SDL_Rect *rect);
     SDL_Rect Get_SDL_Rect();
     void Print(FILE *out=NULL);

     Rectangle &operator=(const SDL_Rect &other)
     {
      x=other.x;
      y=other.y;
      w=other.w;
      h=other.h;
      return *this;
     }
    };

    class Color
    {
     public:
     int r=0,g=0,b=0,a=0;

     Color(int _r,int _g,int _b,int _a = 255);
     SDL_Color Get_SDL_Color();
    };

    void Delay(Uint32 ms);
    const char *Get_error();
}

#endif // WRAPPERS_H
