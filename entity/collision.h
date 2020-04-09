#ifndef COLLISION_H
#define COLLISION_H

#include <memory>
#include <vector>

#include <SDL.h>

#include "body.h"
#include "component.h"
#include "entity.h"
#include "physics.h"
#include "vector2d.h"

using entity_vector = std::vector<std::unique_ptr<entity>>;

class collision : public component {
public:
  collision(entity *ent);

  void handle_collisions(entity_vector &entities) override;

private:
  body *_body;
  physics *_physics;
};

#endif
