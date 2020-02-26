#ifndef INIT_H
#define INIT_H

#include "Utilities.h"

namespace Engine {
    enum Status_flags {
        SDL_INITIALIZED = 1 << 0,
        TTF_INITIALIZED = 1 << 1,
        MIX_INITIALIZED = 1 << 2
    };

    void Init();

    void Init_SDL();

    void Init_TTF();

    void Init_Mix();

    void Close();

    void Close_SDL();

    void Close_TTF();

    void Close_Mix();

    void Print_status(FILE *out = NULL);
}

#endif // INIT_H
