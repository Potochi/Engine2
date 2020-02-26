#ifndef RENDER_H
#define RENDER_H

#include "Texture.h"
#include "Font.h"
#include "Surface_factory.h"

namespace Engine {
    enum Renderer_position {
        RENDERERPOS_CENTERED = 1 << 10
    };

    class Renderer {
    private:
        SDL_Renderer *renderer = NULL;
        SDL_mutex *mutex;
        int flags = 0;
        Surface_factory *surface_factory = NULL;
        Texture *NULL_texture = NULL;
        int w = 0, h = 0;

    public:
        void Open(SDL_Window *window, int _flags, SDL_PixelFormat *pixel_format);

        void Close();

        void ReOpen(SDL_Window *Window, int _flags, SDL_PixelFormat *pixel_format);

        Texture *Load_texture(std::string filename);

        Texture *Create_transparent_texture(int w, int h);

        Texture *Create_TTF_texture(Font *font, std::string text, Color color);

        void Set_texture_blend_mode(Texture *texture, SDL_BlendMode blend_mode);

        void Set_texture_alpha(Texture *texture, Uint8 alpha);

        void Draw_texture(Rectangle src_rect, Texture *src, Rectangle dst_rect);

        void Draw_texture(int x, int y, Texture *source);

        void Draw_texture(int x, int y, Texture *source, Texture *destination);

        void Flush();

        void Present();
    };

    extern Renderer *RENDERER;

    void Set_global_renderer(Renderer *renderer);

    Texture *Load_texture(std::string filename);
}

#endif // RENDER_H
