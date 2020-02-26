#include "../../CORE/include/Surface.h"

namespace Engine {
    Surface::Surface() {
    }

    Surface::Surface(SDL_Surface *_surf) {
        if (_surf == NULL)
            return;
        image = _surf;
        w = _surf->w;
        h = _surf->h;
    }

    Surface::Surface(int _w, int _h, SDL_Surface *_image) {
        w = _w;
        h = _h;
        image = _image;
    }

    int Surface::Get_w() {
        return w;
    }

    int Surface::Get_h() {
        return h;
    }

    SDL_Surface *Surface::Get_image() {
        return image;
    }

    void Surface::Clear() {
        LOG_INFO("Surface", "Surface cleared");
        SDL_FreeSurface(image);
        image = NULL;
        w = h = 0;
    }
}
