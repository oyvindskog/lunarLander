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

    void set_max_speed(float max) { _max_speed = max; }

    void set_drag(float drag) { _drag = drag; }

    const vector2d& get_speed() const {return _speed;}

    void set_speed(const vector2d& speed) {_speed = speed;}
    
    float get_direction() {return _direction;}

    void set_mass(float mass) { _mass = mass; }

    float get_mass() const { return _mass; }
    
    void impact(const vector2d& force);

    void impact_angular(float force);

    void reset_forces();

    void thrust();

    vector2d get_direction_vector() const;

private: 
    void accelerate();
    void accelerate_angular(); 
    vector2d _gravity = {0, 0};
    vector2d _speed = {0, 0};
    float _max_speed = 10;
    float _drag = 0.95;

    float _angular_speed = 0;
    float _angular_drag = 0.9;
    float _direction = 270;

    vector2d _acceleration = {0, 0};
    float _angular_acceleration = 0;

    body* body_component = nullptr; 

    float _mass = 10;
    float _force = 0.5;
};

#endif
