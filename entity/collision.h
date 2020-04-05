#ifndef COLLISION_H
#define COLLISION_H

#include <vector>
#include <memory>

#include <SDL.h>

#include "component.h"
#include "vector2d.h"
#include "entity.h"
#include "body.h"
#include "physics.h"

using entity_vector =  std::vector<std::unique_ptr<entity>>;

class collision : public component
{
public:
    collision(entity* ent);

    void handle_collisions(entity_vector& entities) override;

private:
    body* _body;
    physics* _physics;

};

#endif
