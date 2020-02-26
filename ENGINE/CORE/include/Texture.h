#ifndef TEXTURE_H
#define TEXTURE_H

#include "Utilities.h"

namespace Engine {
    class Texture {
    private:
        int w = 0, h = 0;
        SDL_Texture *image = NULL;
        int alpha = 255;

    public:
        Texture(int _w, int _h, SDL_Texture *_image);

        void Set_alpha(int _alpha);

        int Get_w();

        int Get_h();

        int Get_alpha();

        SDL_Texture *Get_image();

        void Clear();
    };

    void Clear_texture(Texture *texture);
}

#endif // TEXTURE_H
