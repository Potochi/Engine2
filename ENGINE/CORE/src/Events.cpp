#include "../include/Events.h"

namespace Engine {
    const Uint8 *Events::keystates = SDL_GetKeyboardState(NULL);

    void Events::Pump_events() {
        SDL_PumpEvents();
    }
}
