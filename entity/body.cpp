#include "body.h"


body::body(entity* e, vector2d&& position, std::vector<part>& parts)
    :component(e),_position(position), _parts(parts){}

void
body::add_part(part&& p)
{
    _parts.emplace_back(p);
}

void
body::render(SDL_Renderer* renderer) const
{
    for (auto p :_parts)
    {
        p.v += _position;
        SDL_Rect rect = { 
            static_cast<int>(p.v.get_x()), 
            static_cast<int>(p.v.get_y()), 
            2, 2
        };
        SDL_SetRenderDrawColor(renderer,
                               p.red,
                               p.green,
                               p.blue, 255);
        SDL_RenderFillRect(renderer, &rect);
        
    }
}

void
body::rotate(double angle)
{
    for (auto& p : _parts) p.v.rotate(angle);
}
