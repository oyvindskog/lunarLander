#ifndef WORLD_H
#define WORLD_H

#include <algorithm>
#include <memory>
#include <vector>

#include <SDL.h>

#include "vector2d.h"
#include "entity_manager.h"
#include "body.h"
#include "physics.h"
#include "key_handler.h"
#include "collision.h"


class world {
public:
    world();

    void update() {_entity_manager->update();}
    
    void move();

    void render(SDL_Renderer* renderer);

    void handle_events(SDL_Event* events);
private:
    std::unique_ptr<entity_manager> _entity_manager;
    
    std::vector<part> _spaceship = {};
};

#endif
