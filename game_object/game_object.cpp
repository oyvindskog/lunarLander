#include "game_object.h"
#include <iostream>

namespace {
constexpr double to_radians = 3.14159265 / 180;
}

game_object::game_object(vector2d&& position)
    : _position(position)
{
}

void game_object::add_bodypart(bodypart&& bodypart)
{
    _body.emplace_back(bodypart);
}

vector2d
game_object::get_position() const
{
    return _position;
}

std::vector<bodypart>&
game_object::get_body()
{
    return _body;
}

void game_object::act()
{
    for (auto behavior : _behaviors) {
        behavior(this);
    }
}

void game_object::move()
{
    _position += _speed;
}

void game_object::accelerate(const vector2d& v)
{
    _speed += v;
}

void game_object::change_direction(const double degrees)
{
    _direction += degrees;
    for (auto& b : _body) {
        b.v.rotate(degrees);
    }
}

double
game_object::get_direction() const
{
    return _direction;
}

vector2d
game_object::get_direction_vector() const
{
    return vector2d(cos(_direction * to_radians),
        sin(_direction * to_radians));
}

void game_object::add_behavior(std::function<void(game_object*)> behavior)
{
    _behaviors.emplace_back(behavior);
}

void game_object::kill()
{
    _dead = { true, 0 };
}
