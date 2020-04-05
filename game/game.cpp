#include "game.h"
#include <iostream>

game::game()
{
    _world = std::make_unique<world>();
}

game::~game()
{
}

void game::init(const char* title, int x, int y, int width, int height)
{
    int flags = 0;

    if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {

        std::cout << "Subsystem initialized" << std::endl;
        window = SDL_CreateWindow("title", x, y, width, height, flags);
        if (window) {
            std::cout << "Window created" << std::endl;
        }
        renderer = SDL_CreateRenderer(window, -1, 0);
        if (renderer) {
            SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
            std::cout << "Renderer created" << std::endl;
        }

        backDestRect.x = 0;
        backDestRect.y = 0;
        backDestRect.w = width;
        backDestRect.h = height;

        isRunning = true;

    } else {
        isRunning = false;
    }
}

void game::handleEvents()
{

    SDL_Event event;
    SDL_PollEvent(&event);
    _world->handle_events(&event);
    switch (event.type) {
    case SDL_QUIT:
        isRunning = false;
        break;
    default:
        break;
    }

    _world->reset_keypress();
    const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
    if (currentKeyStates[SDL_SCANCODE_UP]) {
        _world->handle_keypress(key::up);
    }
    if (currentKeyStates[SDL_SCANCODE_LEFT]) {
        _world->handle_keypress(key::left);
    }
    if (currentKeyStates[SDL_SCANCODE_RIGHT]) {
        _world->handle_keypress(key::right);
    }
    if (currentKeyStates[SDL_SCANCODE_LCTRL]) {
        auto current_time = SDL_GetTicks();
        if (current_time > _last_keypress + 1000) {
            _world->handle_keypress(key::shoot);
            _last_keypress = current_time;
        }
    }

    _world->detect_collision();
}

void game::render()
{
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
    SDL_RenderFillRect(renderer, &backDestRect);
    _world->render(renderer);
    SDL_RenderPresent(renderer);
}

void game::update()
{
    _world->remove_dead_objects();
    _world->update();
    _world->move();
}

void game::clean()
{
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    std::cout << "game cleaned" << std::endl;
}

bool game::running()
{
    return isRunning;
}
