#ifndef COMPONENT_H
#define COMPONENT_H

#include <SDL.h>
#include <array>
#include <bitset>
#include <iostream>
#include <memory>
#include <vector>

class entity;
class SDL_Renderer;

class component {
public:
  component() {}
  component(entity *initEntity) : _ent(initEntity) {}
  virtual ~component() {}

  virtual void handle_events(SDL_Event *event) {}
  virtual void update() {}
  virtual void render(SDL_Renderer *renderer) const {}

  virtual void handle_collisions(std::vector<std::unique_ptr<entity>> &) {}
  entity *_ent; // entity that owns the component
};

#endif // COMPONENT_H
