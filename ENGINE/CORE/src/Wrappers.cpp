#include "../../CORE/include/Wrappers.h"

namespace Engine
{
    Rectangle::Rectangle()
    {
    }

    Rectangle::Rectangle(int _x,int _y,int _w,int _h)
    {
     x=_x;
     y=_y;
     w=_w;
     h=_h;
    }

    Rectangle::Rectangle(int _x,int _y)
    {
     x=_x;
     y=_y;
     w=h=0;
    }

    Rectangle::Rectangle(SDL_Rect *rect)
    {
     Rectangle(rect->x,rect->y,rect->w,rect->h);
    }

    SDL_Rect Rectangle::Get_SDL_Rect()
    {
     SDL_Rect rect={x,y,w,h};
     return rect;
    }

    void Rectangle::Print(FILE *out)
    {
     if(out==NULL)
        out=stderr;
     fprintf(stderr,"Rect {%d, %d, %d, %d}\n",x,y,w,h);
    }

    Color::Color(int _r,int _g,int _b,int _a)
    {
     r=_r;
     g=_g;
     b=_b;
     a=_a;
    }

    SDL_Color Color::Get_SDL_Color()
    {
     SDL_Color color;
     color.r=r;
     color.g=g;
     color.b=b;
     color.a=a;
     return color;
    }

    void Delay(Uint32 ms)
    {
     SDL_Delay(ms);
    }

    const char *Get_error()
    {
     return SDL_GetError();
    }
}
