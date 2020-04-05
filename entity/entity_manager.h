#ifndef ENTITYMANAGER_H
#define ENTITYMANAGER_H

#include <vector>
#include <memory>
#include "entity.h"

using entity_vector =  std::vector<std::unique_ptr<entity>>;

class entity_manager
{
    public:
        entity_manager(){}
        virtual ~entity_manager(){}

        void addEntity(entity*);
        void handle_events(SDL_Event *event);
        void update() const;
        void render(SDL_Renderer *renderer) const;
        void refresh();
    private:
        entity_vector _entities;

};

#endif // ENTITYMANAGER_H
