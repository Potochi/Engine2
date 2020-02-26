#include "../include/Font.h"

namespace Engine {
    void Font::Load(std::string filename, int ptr_size) {
        if (filename.empty()) {
            LOG_ERROR("Renderer", "Could not load font, filename is null");
            return;
        }
        font = TTF_OpenFont(filename.c_str(), ptr_size);
        if (font == NULL) {
            LOG_ERROR("Renderer", "Could not load font: %s", Get_error());
            return;
        }
        LOG_INFO("Renderer", "Loaded font: name=[%s]", filename.c_str());
    }

    void Font::Clear() {
        TTF_CloseFont(font);
        font = NULL;
        LOG_INFO("Renderer", "Closed font");
    }

    Font *Load_font(std::string filename) {
        std::size_t q;
        q = filename.find(".ttf");
        if (q == std::string::npos)
            q = filename.find(".TTF");
        if (q == std::string::npos) {
            LOG_ERROR("Renderer", "Wrong format (.ttf) is missing");
            return nullptr;
        }
        Font *font = new Font;
        font->Load(filename, 80);
        return font;
    }

    void Clear_font(Font *font) {
        font->Clear();
        delete font;
    }
}
