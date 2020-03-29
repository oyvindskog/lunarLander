#ifndef WORLD_H
#define WORLD_H

#include <algorithm>
#include <memory>
#include <vector>

#include <SDL.h>

#include "game_object.h"
#include "vector2d.h"

enum class object_type {
    movable,
    immovable,
};

enum class key {
    up,
    left,
    right,
    shoot,
};

class world {
public:
    world();

    void add_game_object(game_object* object, object_type type);

    void move();

    void render(SDL_Renderer* renderer);

    void handle_keypress(key k);

    void reset_keypress();

    void detect_collision() const;

    void remove_dead_objects();

private:
    std::vector<std::unique_ptr<game_object>> _movables;
    std::unique_ptr<game_object> _player = nullptr;

    bool _up = false;
    bool _left = false;
    bool _right = false;
    bool _shoot = false;
};

#endif
