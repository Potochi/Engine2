#ifndef EVENTS_H
#define EVENTS_H

#include "Wrappers.h"
#include "Scancodes.h"

namespace Engine {
    class Events {
    public:
        static const Uint8 *keystates;

        static void Pump_events();
    };
}

#endif // EVENTS_H
