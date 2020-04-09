#ifndef BODY_COMPONENT_H
#define BODY_COMPONENT_H

#include "component.h"
#include "vector2d.h"
#include <vector>

struct part {
  vector2d v;
  int red;
  int green;
  int blue;
};

class body : public component {

public:
  body(entity *e, vector2d &&position, std::vector<part> &parts);

  void add_part(part &&);

  void render(SDL_Renderer *renderer) const override;

  void position_add(const vector2d &speed) { _position += speed; }

  void rotate(float angle);

  const vector2d &get_position() const { return _position; }

  const std::vector<part> &get_parts() const { return _parts; }

private:
  vector2d _position;
  std::vector<part> _parts;
};

#endif
