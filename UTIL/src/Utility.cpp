#include "../include/Utility.h"
#include <assert.h>

namespace UTIL {
    bool Set_console_size(int width, int height) {
// TODO reimplement to be platrofm agnostic
#ifdef FIXED
        _COORD coord;
        coord.X = width;
        coord.Y = height;

        _SMALL_RECT Rect;
        Rect.Top = 0;
        Rect.Left = 0;
        Rect.Bottom = height - 1;
        Rect.Right = width - 1;

        HANDLE Handle = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleScreenBufferSize(Handle, coord);

        SetConsoleWindowInfo(Handle, true, &Rect);

        return true;
#endif
    }

}
