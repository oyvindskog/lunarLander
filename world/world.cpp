#include "world.h"
#include <SDL2/SDL_image.h>
#include <iostream>

world::world() {
  _spaceship = {
      {vector2d(-1, -10), 0, 255, 0}, {vector2d(-3, -8), 0, 255, 0},
      {vector2d(-1, -8), 0, 0, 0},    {vector2d(1, -8), 0, 255, 0},
      {vector2d(-5, -6), 0, 255, 0},  {vector2d(-3, -6), 0, 0, 0},
      {vector2d(-1, -6), 0, 0, 0},    {vector2d(1, -6), 0, 0, 0},
      {vector2d(3, -6), 0, 255, 0},   {vector2d(-5, -4), 0, 255, 0},
      {vector2d(-3, -4), 0, 0, 0},    {vector2d(-1, -4), 0, 0, 0},
      {vector2d(1, -4), 0, 0, 0},     {vector2d(3, -4), 0, 255, 0},
      {vector2d(-3, -2), 0, 255, 0},  {vector2d(-1, -2), 0, 255, 0},
      {vector2d(1, -2), 0, 255, 0},   {vector2d(-3, 0), 0, 255, 0},
      {vector2d(-1, 0), 0, 255, 0},   {vector2d(1, 0), 0, 255, 0},
      {vector2d(-3, 2), 0, 255, 0},   {vector2d(-1, 2), 0, 255, 0},
      {vector2d(1, 2), 0, 255, 0},    {vector2d(-1, 4), 0, 255, 0},
      {vector2d(-3, 6), 0, 255, 0},   {vector2d(-1, 6), 0, 255, 0},
      {vector2d(1, 6), 0, 255, 0},    {vector2d(-5, 8), 0, 255, 0},
      {vector2d(-3, 8), 0, 255, 0},   {vector2d(-1, 8), 0, 255, 0},
      {vector2d(1, 8), 0, 255, 0},    {vector2d(3, 8), 0, 255, 0},
  };

  _entity_manager = std::make_unique<entity_manager>();

  entity *e = new entity();
  e->add_component<body>(vector2d(100, 100), _spaceship);
  e->add_component<physics>(vector2d(0, 0));
  e->add_component<collision>();
  e->add_component<key_handler>();
  _entity_manager->addEntity(e);

  for (int i = 0; i < 50; i++) {
    e = new entity();
    double x = static_cast<double>(rand() % 790 + 10);
    double y = static_cast<double>(rand() % 630 + 10);
    e->add_component<body>(vector2d(x, y), _spaceship);
    e->add_component<physics>(vector2d(0, 0));
    e->get_component<physics>().set_mass(10);
    e->add_component<collision>();
    e->get_component<body>().add_part({vector2d(3, 8), 255, 0, 0});
    e->get_component<body>().add_part({vector2d(1, 8), 255, 0, 0});
    e->get_component<body>().add_part({vector2d(-1, 8), 255, 0, 0});
    _entity_manager->addEntity(e);
  }
}

void world::render(SDL_Renderer *renderer) {
  _entity_manager->render(renderer);
}

void world::handle_events(SDL_Event *events) {
  _entity_manager->handle_events(events);
}
