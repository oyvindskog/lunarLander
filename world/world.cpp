#include "world.h"
#include "behavior.h"
#include <SDL2/SDL_image.h>
#include <iostream>

namespace {

constexpr auto init_player_body = [](game_object* player) {
    player->add_bodypart({ vector2d(-1, -10), 0, 255, 0 });
    player->add_bodypart({ vector2d(-3, -8), 0, 255, 0 });
    player->add_bodypart({ vector2d(-1, -8), 0, 0, 0 });
    player->add_bodypart({ vector2d(1, -8), 0, 255, 0 });
    player->add_bodypart({ vector2d(-5, -6), 0, 255, 0 });
    player->add_bodypart({ vector2d(-3, -6), 0, 0, 0 });
    player->add_bodypart({ vector2d(-1, -6), 0, 0, 0 });
    player->add_bodypart({ vector2d(1, -6), 0, 0, 0 });
    player->add_bodypart({ vector2d(3, -6), 0, 255, 0 });
    player->add_bodypart({ vector2d(-5, -4), 0, 255, 0 });
    player->add_bodypart({ vector2d(-3, -4), 0, 0, 0 });
    player->add_bodypart({ vector2d(-1, -4), 0, 0, 0 });
    player->add_bodypart({ vector2d(1, -4), 0, 0, 0 });
    player->add_bodypart({ vector2d(3, -4), 0, 255, 0 });
    player->add_bodypart({ vector2d(-3, -2), 0, 255, 0 });
    player->add_bodypart({ vector2d(-1, -2), 0, 255, 0 });
    player->add_bodypart({ vector2d(1, -2), 0, 255, 0 });
    player->add_bodypart({ vector2d(-3, 0), 0, 255, 0 });
    player->add_bodypart({ vector2d(-1, 0), 0, 255, 0 });
    player->add_bodypart({ vector2d(1, 0), 0, 255, 0 });
    player->add_bodypart({ vector2d(-3, 2), 0, 255, 0 });
    player->add_bodypart({ vector2d(-1, 2), 0, 255, 0 });
    player->add_bodypart({ vector2d(1, 2), 0, 255, 0 });
    player->add_bodypart({ vector2d(-1, 4), 0, 255, 0 });
    player->add_bodypart({ vector2d(-3, 6), 0, 255, 0 });
    player->add_bodypart({ vector2d(-1, 6), 0, 255, 0 });
    player->add_bodypart({ vector2d(1, 6), 0, 255, 0 });
    player->add_bodypart({ vector2d(-5, 8), 0, 255, 0 });
    player->add_bodypart({ vector2d(-3, 8), 0, 255, 0 });
    player->add_bodypart({ vector2d(-1, 8), 0, 255, 0 });
    player->add_bodypart({ vector2d(1, 8), 0, 255, 0 });
    player->add_bodypart({ vector2d(3, 8), 0, 255, 0 });
};

constexpr auto init_seeker_body = [](game_object* seeker) {
    seeker->add_bodypart({ vector2d(-3, -2), 0, 255, 0 });
    seeker->add_bodypart({ vector2d(-1, -2), 0, 255, 0 });
    seeker->add_bodypart({ vector2d(1, -2), 0, 255, 0 });
    seeker->add_bodypart({ vector2d(-3, 0), 0, 255, 0 });
    seeker->add_bodypart({ vector2d(-1, 0), 0, 255, 0 });
    seeker->add_bodypart({ vector2d(1, 0), 0, 255, 0 });
};

SDL_Rect game_object_rect(const vector2d& v)
{
    SDL_Rect rect;
    rect.x = v.get_x();
    rect.y = v.get_y();
    rect.h = 2;
    rect.w = 2;
    return rect;
}

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
}

world::world()
{
    auto p = new game_object(vector2d(300, 250));

    //p->add_behavior(behavior::gravity());
    p->add_behavior(behavior::friction());
    p->add_behavior([this](game_object* g) {
        if (_up) {
            double force = -0.15;
            g->accelerate(g->get_direction_vector() * force);
        }
        if (_left) {
            g->accelerate_angular(-0.4);
        }
        if (_right) {
            g->accelerate_angular(0.4);
        }
        if (_shoot) {
            auto bullet = new game_object(
                g->get_position() - (g->get_direction_vector() * 12));
            bullet->set_speed(g->get_direction_vector() * -3);
            bullet->add_bodypart({ vector2d(-1, 0), 255, 0, 0 });
            add_game_object(bullet, object_type::movable);
        }
    });
    p->add_behavior([](game_object* g) {
        g->decelerate_angular(0.9);
        g->change_direction(g->get_angular_velocity());
    });
    init_player_body(p);
    _player = std::unique_ptr<game_object>(p);
    srand(time(NULL));
    for (int i = 0; i <= 100; ++i) {
        double x = static_cast<double>(rand() % 790 + 10);
        double y = static_cast<double>(rand() % 630 + 10);

        auto s = new game_object(vector2d(x, y));

        s->add_behavior([this](game_object* g) {
            g->accelerate(
                g->get_position()
                    .direction_to(_player->get_position())
                * 0.005);
            /*for (auto& m : _movables)
            {
                if (g == m.get()) continue;
                if (g->get_position().distance_to(m->get_position()) < 50)
                {
                    g->set_speed(
                        g->get_position()
                         .direction_to(m->get_position()) * -1   
                    );
                }
            }*/
        });
        init_seeker_body(s);
        _movables.emplace_back(std::unique_ptr<game_object>(s));
    }
}

void world::add_game_object(game_object* object, object_type type)
{
    switch (type) {
    case object_type::movable:
        _movables.emplace_back(std::unique_ptr<game_object>(object));
        break;
    }
}

void world::remove_dead_objects()
{
    for (auto it = _movables.begin(); it != _movables.end();) {
        if ((*it)->is_dead()) {
            _movables.erase(it);
        } else {
            it++;
        }
    }
}

void world::move()
{
    for (auto& object : _movables) {
        object->act();
        object->move();
    }
    _player->act();
    _player->move();
}

void world::render(SDL_Renderer* renderer)
{
    auto& body = _player->get_body();
    for (auto bodypart : body) {
        bodypart.v += _player->get_position();
        SDL_Rect rect = game_object_rect(bodypart.v);
        SDL_SetRenderDrawColor(renderer,
            bodypart.red,
            bodypart.green,
            bodypart.blue,
            255);
        SDL_RenderFillRect(renderer, &rect);
    }

    for (auto& m : _movables) {
        for (auto bodypart : m->get_body()) {
            bodypart.v += m->get_position();
            SDL_Rect rect = game_object_rect(bodypart.v);
            SDL_SetRenderDrawColor(renderer,
                bodypart.red,
                bodypart.green,
                bodypart.blue, 255);
            SDL_RenderFillRect(renderer, &rect);
        }
    }
}

void world::reset_keypress()
{
    _up = _left = _right = _shoot = false;
}

void world::handle_keypress(key k)
{
    if (k == key::up) {
        _up = true;
    }
    if (k == key::left) {
        _left = true;
    }
    if (k == key::right) {
        _right = true;
    }
    if (k == key::shoot) {
        _shoot = true;
    }
}

void world::detect_collision() const
{
    int i = 0;
    for (auto& m : _movables) {
        for (auto& b : m->get_body()) {
            for (auto& pb : _player->get_body()) {
                vector2d player_bodypart = _player->get_position() + pb.v;
                vector2d object_bodypart = m->get_position() + b.v;

                if (bodyparts_overlap(player_bodypart, object_bodypart)) {
                    //_player->displace(_player->get_speed());
                    m->displace(m->get_speed());
                    double m_player = 10;
                    double m_m = 10;
                    double combined_m = m_player + m_m;
                    double first = (m_player - m_m) / (combined_m);
                    double second = (2 * m_m) / combined_m;
                    vector2d player_impact = (_player->get_speed() * first) + (m->get_speed() * second);
                    first = (m_m - m_player) / (combined_m);
                    second = (2 * m_player) / combined_m;
                    vector2d m_impact = (m->get_speed() * first) + (_player->get_speed() * second);
                    _player->set_speed(player_impact);
                    //auto impact_player = (m->get_speed() - _player->get_speed()) * 0.2;
                    m->set_speed(m_impact);
                    //auto impact_m = (_player->get_speed()- m->get_speed()) * 0.5;
                    //_player->accelerate(impact_player - impact_m);
                    //m->accelerate(impact_m - impact_player);
                    //m->kill();
                    return;
                }
            }
        }
    }
}
