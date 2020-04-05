#include "entity_manager.h"
#include <algorithm>

void entity_manager::addEntity(entity *ent) {
    _entities.emplace_back( std::unique_ptr<entity> {ent} );
}


void entity_manager::handle_events(SDL_Event *event) {
    for (auto &e : _entities) e->handle_events(event);
    for (auto& e : _entities) e->handle_collisions(_entities);
}

void entity_manager::update() const {
    for (auto& e : _entities) e->update();
}

void entity_manager::render(SDL_Renderer *renderer) const{
    for (auto &e : _entities)
    {
        e->render(renderer);
    }
}

void entity_manager::refresh(){

    _entities.erase(std::remove_if(begin(_entities), end(_entities),
                [](const std::unique_ptr<entity> &ent){
        return !ent->isActive();
    }), end(_entities));
}

