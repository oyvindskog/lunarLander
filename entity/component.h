#ifndef COMPONENT_H
#define COMPONENT_H

#include <bitset>
#include <array>
#include <iostream>
#include <SDL.h>
#include <vector>
#include <memory>

class entity;
class SDL_Renderer;


class component
{
    public:
        component(){}
        component(entity *initEntity):_ent(initEntity){}
        virtual ~component(){}

        virtual void handle_events(SDL_Event *event){}
        virtual void update(){}
        virtual void render(SDL_Renderer *renderer) const{}
        
        virtual void handle_collisions(std::vector<std::unique_ptr<entity>>&){}
        entity* _ent; // entity that owns the component
};

#endif // COMPONENT_H
