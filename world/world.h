#ifndef WORLD_H
#define WORLD_H

#include <algorithm>
#include <memory>
#include <vector>

#include <SDL.h>

#include "game_object.h"
#include "vector2d.h"
#include "entity_manager.h"
#include "body.h"
#include "physics.h"
#include "key_handler.h"
#include "collision.h"

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

    void update() {_entity_manager->update();}
    
    void move();

    void render(SDL_Renderer* renderer);

    void handle_keypress(key k);

    void reset_keypress();

    void detect_collision() const;

    void remove_dead_objects();
    
    void handle_events(SDL_Event* events) { _entity_manager->handle_events(events);}
private:
    std::vector<std::unique_ptr<game_object>> _movables;
    std::unique_ptr<game_object> _player = nullptr;
    std::unique_ptr<entity_manager> _entity_manager;
    
    std::vector<part> _spaceship = {};
    bool _up = false;
    bool _left = false;
    bool _right = false;
    bool _shoot = false;
};

#endif
