#include "collision.h"


bool bodyparts_overlap(const vector2d& sq1, const vector2d& sq2)
{
    const auto sq1_r = sq1 + vector2d(2, 2);
    const auto sq2_r = sq2 + vector2d(2, 2);
    if (sq1.get_x() > sq2_r.get_x() || sq2.get_x() > sq1_r.get_x()) {
        return false;
    }
    if (sq1.get_y() > sq2_r.get_y() || sq2.get_y() > sq1_r.get_y()) {
        return false;
    }
    return true;
}

collision::collision(entity* ent)
:component(ent)
{
    if (_ent->has_component<body>()){
        _body = &_ent->get_component<body>();
    }

    if (_ent->has_component<physics>()){
        _physics = &_ent->get_component<physics>();
    }
}

void
collision::handle_collisions(entity_vector& entities)
{
    for (auto& e : entities) {
        if (e.get() == _ent || 
            !e->has_component<collision>()) continue;
            
        auto e_body = e->get_component<body>();
        auto e_physics = e->get_component<physics>();
        
        for (auto& p : e_body.get_parts()) {
            for (auto& this_p : _body->get_parts()) {
                
                vector2d this_pp = _body->get_position() + this_p.v;
                vector2d pp = e_body.get_position() + p.v;

                if (bodyparts_overlap(pp, this_pp)) {
                    
                    double m_this = _physics->get_mass();
                    double m_e = e_physics.get_mass();
                    double combined_m = m_this + m_e;
                    
                    double first = (m_this - m_e) / (combined_m);
                    double second = (2 * m_e) / combined_m;
                    vector2d this_impact = (_physics->get_speed() * first) + 
                                           (e_physics.get_speed() * second);

                    _physics->accelerate(this_impact);
                    return;
                }
            }
        }
    }
}
