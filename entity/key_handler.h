#ifndef KEY_HANDLER_H
#define KEY_HANDLER_H

#include "component.h"
#include "entity.h"
#include "physics.h"

class key_handler : public component {
public:
  key_handler(entity *);

  void handle_events(SDL_Event *) override;

private:
  physics *_physics = nullptr;
};

#endif
