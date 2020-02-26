#ifndef ECS_ENTITY_H
#define ECS_ENTITY_H

#include "../../UTIL/UTIL.h"
#include "../../LOG/LOG.h"

namespace ECS {
    class Engine;

    struct Entity {
    public:
        int id;

        Entity(int _id = -1) : id(_id) {};

        bool operator<(const Entity &other) const {
            return id < other.id;
        }

        bool operator==(const Entity &other) const {
            return id == other.id;
        }
    };
}

#endif // ECS_ENTITY_H
