#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include <functional>
#include <vector>

#include "vector2d.h"

struct bodypart {
    vector2d v;
    int red;
    int green;
    int blue;
};

class game_object {

public:
    game_object(vector2d&& position);

    void add_bodypart(bodypart&&); //vector2d&& bodypart);

    vector2d get_position() const;

    std::vector<bodypart>& get_body();

    double get_direction() const;

    vector2d get_direction_vector() const;

    double get_angular_velocity() const { return _angular_velocity; }

    void set_speed(const vector2d& speed) { _speed = speed; }

    const vector2d& get_speed() const { return _speed; }

    void act();

    void move();

    void displace(const vector2d& v) { _position += v; }

    void accelerate(const vector2d& v);

    void adjust_speed(double scalar) { _speed *= scalar; }

    void accelerate_angular(double force) { _angular_velocity += force; }

    void decelerate_angular(double mult) { _angular_velocity *= mult; }

    void change_direction(const double degrees);

    void add_behavior(std::function<void(game_object*)>);

    void kill();

    bool is_dead() { return _dead.first == true; };

private:
    vector2d _position = vector2d(0, 0);
    vector2d _speed = vector2d(0, 0);
    double _angular_velocity = 0;
    double _direction = 90;
    std::vector<bodypart> _body;
    std::vector<std::function<void(game_object*)>> _behaviors;
    std::pair<bool, int> _dead = { false, 0 };
};

#endif
