#include "behavior.h"

namespace behavior {
std::function<void(game_object*)> gravity()
{
    return [](game_object* g) {
        g->accelerate(vector2d(0, 0.07));
    };
}

std::function<void(game_object*)> friction()
{
    return [](game_object* g) {
        g->adjust_speed(0.99);
    };
}
}
