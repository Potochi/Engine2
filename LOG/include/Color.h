#ifndef COLOR_H
#define COLOR_H


namespace LOG
{
#ifdef WINDOWS_CODE
    enum Color
    {
     TEXT_BLUE=     FOREGROUND_BLUE,
     TEXT_GREEN=    FOREGROUND_GREEN,
     TEXT_RED=      FOREGROUND_RED,
     TEXT_CYAN=     TEXT_GREEN | TEXT_BLUE,
     TEXT_MAGENTA=  TEXT_RED | TEXT_BLUE,
     TEXT_YELLOW=   TEXT_RED | TEXT_GREEN,
     TEXT_WHITE=    TEXT_RED | TEXT_GREEN | TEXT_BLUE,
     TEXT_INTENSITY=FOREGROUND_INTENSITY,
     BG_BLUE=       BACKGROUND_BLUE,
     BG_GREEN=      BACKGROUND_GREEN,
     BG_RED=        BACKGROUND_RED,
     BG_CYAN=       BG_GREEN | BG_BLUE,
     BG_MAGENTA=    BG_RED | BG_BLUE,
     BG_YELLOW=     BG_RED | BG_GREEN,
     BG_WHITE=      BG_RED | BG_GREEN | BG_BLUE,
     BG_INTENSITY=  BACKGROUND_INTENSITY
    };
#endif
    class Console_painter
    {
     private:
//     HANDLE console;

     public:
     void Init();
     void Change_color(int color);
     void Reset_color();
    };
}


#endif // COLOR_H
