#include "physics.h"
#include "entity.h"

physics::physics(entity *e, vector2d &&gravity)
    : component(e), _gravity(gravity) {
  if (_ent->has_component<body>()) {
    body_component = &_ent->get_component<body>();
  }
}

void physics::update() {
  impact(_gravity);
  accelerate_angular();
  accelerate();

  body_component->rotate(_angular_speed);
  _speed *= _drag;
  if (_speed.length() > _max_speed) {
    _speed = _speed.unit() * _max_speed;
  }
  _direction += _angular_speed;

  if (_direction > 360) {
    _direction -= 360;
  } else if (_direction < 0) {
    _direction += 360;
  }

  _angular_speed *= _angular_drag;
  move();
  reset_forces();
}

void physics::thrust() { impact(get_direction_vector() * _force); }

void physics::accelerate_angular() { _angular_speed += _angular_acceleration; }

vector2d physics::get_direction_vector() const {
  constexpr float to_radians = 3.14159265 / 180;
  return vector2d(cos(_direction * to_radians), sin(_direction * to_radians));
}

void physics::impact(const vector2d &force) { _acceleration += force; }

void physics::impact_angular(float force) { _angular_acceleration += force; }

void physics::reset_forces() {
  _acceleration = {0, 0};
  _angular_acceleration = 0;
}

void physics::move() { body_component->position_add(_speed); }

void physics::accelerate() { _speed += _acceleration; }
