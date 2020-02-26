#include "../../CORE/include/Texture.h"

namespace Engine {
    Texture::Texture(int _w, int _h, SDL_Texture *_image) {
        w = _w;
        h = _h;
        image = _image;
    }

    void Texture::Set_alpha(int _alpha) {
        alpha = _alpha;
    }

    int Texture::Get_w() {
        return w;
    }

    int Texture::Get_h() {
        return h;
    }

    int Texture::Get_alpha() {
        return alpha;
    }

    SDL_Texture *Texture::Get_image() {
        return image;
    }

    void Texture::Clear() {
        SDL_DestroyTexture(image);
        image = NULL;
        w = h = 0;
        alpha = 255;
    }

    void Clear_texture(Texture *texture) {
        texture->Clear();
        texture = nullptr;
        LOG_INFO("Renderer", "Destroyed texture");
    }
}
