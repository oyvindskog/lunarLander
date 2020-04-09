#ifndef GAME_H
#define GAME_H

#include <SDL.h>

#include "world.h"
#include <memory>

class game {
public:
  game();
  virtual ~game();

  void init(const char *title, int x, int y, int width, int height);
  void clean();
  bool running();
  void render();
  void update();
  void handleEvents();

private:
  bool isRunning;

  SDL_Window *window = nullptr;
  SDL_Texture *backgroundTexture = nullptr;
  SDL_Rect backSrcRect, backDestRect;
  SDL_Renderer *renderer = nullptr;

  std::unique_ptr<world> _world = nullptr;
  Uint32 _last_keypress = 0;
};

#endif // GAME_H
