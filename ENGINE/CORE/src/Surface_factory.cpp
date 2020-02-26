#include "../../CORE/include/Surface_factory.h"

namespace Engine {
    const Color TRANSPARENT_COLOR = Color(0xFF, 0x0, 0xE1, 0);

    Surface_factory::Surface_factory(SDL_PixelFormat *_format) {
        Open(_format);
    }

    void Surface_factory::Open(SDL_PixelFormat *_format) {
        format = _format;
        NULL_surface = new Surface;

        LOG_INFO("Surface", "Surface factory opened");
    }

    Surface_factory::~Surface_factory() {
        Close();
    }

    void Surface_factory::Close() {
        format = NULL;
        delete NULL_surface;
        NULL_surface = NULL;

        LOG_INFO("Surface", "Surface factory closed");
    }

    Surface *Surface_factory::Load(std::string filename) {
        if (filename.empty()) {
            LOG_WARNING("Surface", "Could not load surface: filename is empty");
            return NULL_surface;
        }
        SDL_Surface *loadedImage = NULL;
        loadedImage = Load_surface(filename.c_str());
        if (loadedImage == NULL) {
            LOG_WARNING("Surface", "Could not load surface: %s", Get_error());
            return NULL_surface;
        }
        //SDL_Surface *optimizedImage=SDL_ConvertSurface(loadedImage,format,NULL);
        //SDL_FreeSurface(loadedImage);
        /*if(optimizedImage==NULL)
           {
            SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_WARNING,"Could not optimize surface",Get_error(),NULL);
            return NULL_surface;
           }*/

        Surface *surface;
        //surface=new Surface(optimizedImage);
        surface = new Surface(loadedImage);

        LOG_INFO("Surface", "Loaded surface: %s", filename.c_str());

        return surface;
    }

    Surface *Surface_factory::Get_NULL_surface() {
        return NULL_surface;
    }

    SDL_Surface *Load_surface(std::string filename) {
        SDL_Surface *loadedImage = NULL;
        loadedImage = IMG_Load(filename.c_str());
        if (loadedImage != NULL) {
            Uint32 colorkey = SDL_MapRGB(loadedImage->format, TRANSPARENT_COLOR.r, TRANSPARENT_COLOR.g,
                                         TRANSPARENT_COLOR.b);
            Uint8 r, g, b;
            SDL_GetRGB(colorkey, loadedImage->format, &r, &g, &b);
            if (r == TRANSPARENT_COLOR.r &&
                g == TRANSPARENT_COLOR.g &&
                b == TRANSPARENT_COLOR.b)
                SDL_SetColorKey(loadedImage, SDL_TRUE, colorkey);
        }
        return loadedImage;
    }
}
