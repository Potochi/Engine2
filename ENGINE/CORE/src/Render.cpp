#include "../../CORE/include/Render.h"

namespace Engine {
    void Renderer::Open(SDL_Window *window, int _flags, SDL_PixelFormat *pixel_format) {
        flags = _flags;
        renderer = SDL_CreateRenderer(window, -1, _flags);
        if (renderer == NULL) {
            LOG_CRITICAL("Renderer", "Could not create renderer: %s", Get_error());
            exit(-1);
        }
        mutex = SDL_CreateMutex();
        if (mutex == NULL) {
            LOG_CRITICAL("Renderer", "Could not create mutex: %s", Get_error());
            exit(-1);
        }
        surface_factory = new Surface_factory(pixel_format);

        NULL_texture = new Texture(0, 0, NULL);
        SDL_GetWindowSize(window, &w, &h);

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        LOG_INFO("Renderer", "Renderer opened");
    }

    void Renderer::Close() {
        SDL_DestroyRenderer(renderer);
        SDL_DestroyMutex(mutex);
        delete surface_factory;
        surface_factory = NULL;
        delete NULL_texture;
        w = h = 0;
        LOG_INFO("Renderer", "Renderer closed");
    }

    void Renderer::ReOpen(SDL_Window *window, int _flags, SDL_PixelFormat *pixel_format) {
        Close();
        Open(window, _flags, pixel_format);
    }

    Texture *Renderer::Load_texture(std::string filename) {
        Surface *image_surface = surface_factory->Load(filename);
        if (image_surface == surface_factory->Get_NULL_surface())
            return NULL_texture;
        SDL_LockMutex(mutex);
        SDL_Texture *image_texture = SDL_CreateTextureFromSurface(renderer, image_surface->Get_image());
        if (image_texture == NULL) {
            LOG_ERROR("Renderer", "Could not load texture: %s", Get_error());
            return NULL_texture;
        }
        SDL_UnlockMutex(mutex);

        Texture *texture;
        texture = new Texture(image_surface->Get_w(), image_surface->Get_h(), image_texture);

        image_surface->Clear();

        LOG_INFO("Renderer", "Loaded texture: %s", filename.c_str());

        return texture;
    }

    Texture *Renderer::Create_transparent_texture(int w, int h) {
        SDL_LockMutex(mutex);
        Texture *_texture = NULL;
        _texture = new Texture(w, h,
                               SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, w, h));
        SDL_SetRenderTarget(renderer, _texture->Get_image());
        SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
        SDL_SetTextureBlendMode(_texture->Get_image(), SDL_BLENDMODE_BLEND);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
        SDL_RenderClear(renderer);
        SDL_SetRenderTarget(renderer, NULL);
        SDL_UnlockMutex(mutex);
        if (_texture->Get_image() == NULL) {
            LOG_ERROR("Renderer", "Could not create transparent texture: %s", Get_error());
            return NULL_texture;
        }

        LOG_INFO("Renderer", "Created transparent texture: w=%d,h=%d", w, h);
        return _texture;
    }

    Texture *Renderer::Create_TTF_texture(Font *font, std::string text, Color color) {
        if (font == NULL || font->font == NULL) {
            LOG_ERROR("Renderer", "Could not create TTF texture: font is null");
            return NULL_texture;
        }

        SDL_Surface *image_surface = TTF_RenderText_Blended(font->font, text.c_str(), color.Get_SDL_Color());
        if (image_surface == NULL)
            return NULL;
        SDL_LockMutex(mutex);
        SDL_Texture *image_texture = SDL_CreateTextureFromSurface(renderer, image_surface);
        if (image_texture == NULL) {
            LOG_ERROR("Renderer", "Could not create TTF texture: %s", Get_error());
            return NULL_texture;
        }
        SDL_UnlockMutex(mutex);

        Texture *texture;
        texture = new Texture(image_surface->w, image_surface->h, image_texture);

        SDL_FreeSurface(image_surface);
        LOG_INFO("Renderer", "Created TTF texture: text=[%s]", text.c_str());
        return texture;
    }

    void Renderer::Set_texture_blend_mode(Texture *texture, SDL_BlendMode blend_mode) {
        if (texture == nullptr || texture->Get_image() == nullptr)
            return;
        SDL_LockMutex(mutex);
        SDL_SetTextureBlendMode(texture->Get_image(), blend_mode);
        SDL_UnlockMutex(mutex);
    }

    void Renderer::Set_texture_alpha(Texture *texture, Uint8 alpha) {
        if (texture == nullptr || texture->Get_image() == nullptr || texture->Get_alpha() == alpha)
            return;
        SDL_BlendMode blendmode;
        SDL_GetTextureBlendMode(texture->Get_image(), &blendmode);
        if (blendmode != SDL_BLENDMODE_BLEND)
            Set_texture_blend_mode(texture, SDL_BLENDMODE_BLEND);
        SDL_GetTextureBlendMode(texture->Get_image(), &blendmode);
        SDL_LockMutex(mutex);
        SDL_SetTextureAlphaMod(texture->Get_image(), alpha);
        SDL_UnlockMutex(mutex);
        texture->Set_alpha(alpha);
    }

    void Renderer::Draw_texture(Rectangle src_rect, Texture *src, Rectangle dst_rect) {
        if (src == NULL || src->Get_image() == NULL) {
            LOG_ERROR("Renderer", "Could not draw NULL texture");
            return;
        }

        SDL_LockMutex(mutex);
        SDL_Rect src_offset = src_rect.Get_SDL_Rect();
        SDL_Rect dst_offset = dst_rect.Get_SDL_Rect();
        SDL_RenderCopy(renderer, src->Get_image(), &src_offset, &dst_offset);
        SDL_UnlockMutex(mutex);
    }

    void Renderer::Draw_texture(int x, int y, Texture *source) {
        if (source == NULL || source->Get_image() == NULL) {
            LOG_ERROR("Renderer", "Could not draw NULL texture");
            return;
        }

        Rectangle offset(x, y, source->Get_w(), source->Get_h());
        if (x == RENDERERPOS_CENTERED)
            offset.x = (w - source->Get_w()) / 2;
        if (y == RENDERERPOS_CENTERED)
            offset.y = (h - source->Get_h()) / 2;
        SDL_LockMutex(mutex);
        SDL_Rect _offset = offset.Get_SDL_Rect();
        SDL_RenderCopy(renderer, source->Get_image(), NULL, &(_offset));
        SDL_UnlockMutex(mutex);
    }

    void Renderer::Draw_texture(int x, int y, Texture *source, Texture *destination) {
        if (source == NULL || source->Get_image() == NULL) {
            LOG_ERROR("Renderer", "Could not draw NULL texture");
            return;
        }
        SDL_LockMutex(mutex);
        if (destination == NULL || destination->Get_image() == NULL) {
            LOG_ERROR("Renderer", "Could not draw to NULL destination texture");
            return;
        }
        Rectangle offset(x, y, source->Get_w(), source->Get_h());
        if (x == RENDERERPOS_CENTERED)
            offset.x = (w - source->Get_w()) / 2;
        if (y == RENDERERPOS_CENTERED)
            offset.y = (h - source->Get_h()) / 2;
        SDL_SetRenderTarget(renderer, destination->Get_image());
        SDL_Rect _offset = offset.Get_SDL_Rect();
        SDL_RenderCopy(renderer, source->Get_image(), NULL, &_offset);
        SDL_SetRenderTarget(renderer, NULL);
        SDL_UnlockMutex(mutex);
    }

    void Renderer::Flush() {
        SDL_RenderClear(renderer);
    }

    void Renderer::Present() {
        SDL_RenderPresent(renderer);
    }

    Renderer *RENDERER = nullptr;

    void Set_global_renderer(Renderer *renderer) {
        RENDERER = renderer;
    }

    Texture *Load_texture(std::string filename) {
        if (RENDERER == nullptr)
            return nullptr;
        return RENDERER->Load_texture(filename);
    }
}
