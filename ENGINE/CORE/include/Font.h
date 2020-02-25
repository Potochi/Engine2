#ifndef FONT_H
#define FONT_H

#include "Utilities.h"
#include <string>

namespace Engine
{
    class Font
    {
     public:
     TTF_Font *font=NULL;

     void Load(std::string filename,int ptr_size);
     void Clear();
    };

    Font *Load_font(std::string filename);
    void Clear_font(Font *font);
}

#endif // FONT_H
