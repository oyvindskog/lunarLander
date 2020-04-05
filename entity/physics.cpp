#include "physics.h"
#include "entity.h"

physics::physics(entity* e, vector2d&& gravity)
:component(e), _gravity(gravity)
{
    if (_ent->has_component<body>())
    {
        body_component = &_ent->get_component<body>();
    }
}

void
physics::update()
{

    body_component->rotate(_angular_speed);
    accelerate(_gravity);
    _speed *= _drag;
    if (_speed.length() > _max_speed)
    {
        _speed = _speed.unit() * _max_speed;
    }
    _direction += _angular_speed;
    if (_direction > 360) _direction -= 360;
    _angular_speed *= _angular_drag;
    move();
}

void
physics::thrust()
{
    accelerate(get_direction_vector() * _force);
}

void
physics::accelerate_angular(double f)
{
    _angular_speed += f; 
}

vector2d 
physics::get_direction_vector() const
{
    constexpr double to_radians = 3.14159265 / 180;
    return vector2d(cos(_direction * to_radians),
                    sin(_direction * to_radians));
}

void
physics::move()
{
    body_component->position_add(_speed); 

}

void
physics::accelerate(const vector2d& v)
{
    _speed += v;
}
