#include "../include/Color.h"

#ifdef WINDOWS_CODE

namespace LOG
{
    void Console_painter::Init()
    {
     console=GetStdHandle(STD_OUTPUT_HANDLE);
    }

    void Console_painter::Change_color(int color)
    {
     SetConsoleTextAttribute(console,color);
    }

    void Console_painter::Reset_color()
    {
     SetConsoleTextAttribute(console,TEXT_WHITE | TEXT_INTENSITY);
    }
};

#endif