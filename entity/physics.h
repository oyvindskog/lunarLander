#ifndef PHYSICS_COMPONENT_H
#define PHYSICS_COMPONENT_H


#include "vector2d.h"
#include "component.h"
#include "body.h"

class entity;

class physics : public component
{

public:
    physics(entity* e, vector2d&& gravity);

    void update() override;

    void move();

    void set_max_speed(double max) { _max_speed = max; }

    void set_drag(double drag) { _drag = drag; }

    const vector2d& get_speed() const {return _speed;}

    void set_speed(const vector2d& speed) {_speed = speed;}
    
    void set_mass(double mass) { _mass = mass; }

    double get_mass() const { return _mass; }

    void accelerate(const vector2d& v);

    void thrust();

    vector2d get_direction_vector() const;

    void accelerate_angular(double f); 
private: 
    vector2d _gravity = {0, 0};
    vector2d _speed = {0, 0};
    double _max_speed = 4;
    double _drag = 0.95;

    double _angular_speed = 0;
    double _angular_drag = 0.9;
    double _direction = 270;
    body* body_component = nullptr; 

    double _mass = 10;
    double _force = 0.5;
};

#endif
