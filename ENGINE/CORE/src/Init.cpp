#include "../../CORE/include/Init.h"

namespace Engine {
    int status = 0;

    void Init() {
        LOG::Init();
        LOG::Set_printing_interval_ms(100);
        LOG::Add_logger("API");
        LOG::Add_logger("Window");
        LOG::Add_logger("Surface");
        LOG::Add_logger("Renderer");
        LOG::Add_logger("ECS");
        LOG::Add_logger("EV BUS");
        LOG::Add_logger("RES MANAGER");
        LOG::Add_logger("Application");
        LOG::Add_logger("Debug");
        Init_SDL();
        Init_TTF();
        Init_Mix();
    }

    void Init_SDL() {
        if (status & SDL_INITIALIZED)
            return;
        if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
            LOG_CRITICAL("API", "SDL_Init failed: %s", Get_error());
            exit(-1);
        }
        status |= SDL_INITIALIZED;

        IMG_Init(IMG_INIT_PNG);
        LOG_INFO("API", "SDL opened");
    }

    void Init_TTF() {
        if (status & TTF_INITIALIZED)
            return;
        if (TTF_Init() == -1) {
            LOG_ERROR("API", "TTF_Init failed: %s", Get_error());
        }
        status |= TTF_INITIALIZED;
        LOG_INFO("API", "SDL_TTF opened");
    }

    void Init_Mix() {
        if (status & MIX_INITIALIZED)
            return;
        if (Mix_Init(MIX_INIT_MP3) & (MIX_INIT_MP3) != MIX_INIT_MP3) {
            LOG_ERROR("API", "Mix_Init failed: %s", Get_error());
        }
        status |= MIX_INITIALIZED;

        if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 4, 4096) == -1) {
            LOG_ERROR("API", "Mix_OpenAudio failed: %s", Get_error());
        }
        LOG_INFO("API", "SDL_Mix opened");
    }

    void Close() {
        Close_TTF();
        Close_Mix();
        Close_SDL();
        LOG::Close();
    }

    void Close_SDL() {
        if (!(status & SDL_INITIALIZED))
            return;
        SDL_Quit();
        status &= ~SDL_INITIALIZED;
        LOG_INFO("API", "SDL closed");
    }

    void Close_TTF() {
        if (!(status & TTF_INITIALIZED))
            return;
        TTF_Quit();
        status &= ~TTF_INITIALIZED;
        LOG_INFO("API", "SDL_TTF closed");
    }

    void Close_Mix() {
        if (!(status & MIX_INITIALIZED))
            return;
        Mix_Quit();
        status &= ~MIX_INITIALIZED;
        LOG_INFO("API", "SDL_Mix closed");
    }

    void Print_status(FILE *out) {
        if (out == NULL)
            out = stderr;
        fprintf(out, "SDL_INIT=%d, TTF_INIT=%d, MIX_INIT=%d\n", bool(status & SDL_INITIALIZED),
                bool(status & TTF_INITIALIZED),
                bool(status & MIX_INITIALIZED));
    }

}

