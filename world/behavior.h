#ifndef BEHAVIOR_H
#define BEHAVIOR_H

#include "world.h"
#include <functional>

namespace behavior {
std::function<void(game_object*)> gravity();

std::function<void(game_object*)> friction();
}

#endif
