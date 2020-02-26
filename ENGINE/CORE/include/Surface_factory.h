#ifndef SURFACE_FACTORY_H
#define SURFACE_FACTORY_H

#include "Surface.h"
#include "Wrappers.h"

namespace Engine {
    class Surface_factory {
    private:
        SDL_PixelFormat *format = NULL;
        Surface *NULL_surface = NULL;

    public:
        Surface_factory(SDL_PixelFormat *_format);

        ~Surface_factory();

        void Open(SDL_PixelFormat *_format);

        void Close();

        Surface *Load(std::string filename);

        Surface *Get_NULL_surface();
    };

    SDL_Surface *Load_surface(std::string filename);
}

#endif // SURFACE_FACTORY_H
