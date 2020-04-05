#include <SDL.h>
#include "key_handler.h"


key_handler::key_handler(entity* ent)
:component(ent)
{
    if (_ent->has_component<physics>()){
        _physics = &_ent->get_component<physics>();
    }
}

void key_handler::handle_events(SDL_Event*) 
{

    const Uint8* currentKeyStates = SDL_GetKeyboardState( NULL );
    if( currentKeyStates[ SDL_SCANCODE_UP ] ){
        _physics->thrust();
    }
    if( currentKeyStates[ SDL_SCANCODE_LEFT ] ){
        _physics->accelerate_angular(-1);
    }
    if( currentKeyStates[ SDL_SCANCODE_RIGHT ] ){
        _physics->accelerate_angular(1);
    }

}

