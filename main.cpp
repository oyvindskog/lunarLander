#include <SDL.h>

#include "game.h"

#include <iostream>
#include <time.h>

game *g = nullptr;

int main(int argc, char **argv) {
  const int FPS = 40;
  const int frameDelay = 1000 / FPS;
  Uint32 frameStart;
  int frameTime;

  // temporary variables to measuse performance
  int64_t num_frames = 0;
  int64_t total_time = 0;

  // initialize srand for random numbers
  srand(time(NULL));

  int windowWidth = 800;
  int windowHeight = 640;

  std::cout << "lets go" << std::endl;
  std::cout << "initializing game..." << std::endl;

  g = new game();
  g->init("My Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
          windowWidth, windowHeight);
  while (g->running()) {
    frameStart = SDL_GetTicks();
    g->update();
    g->handleEvents();
    g->render();
    frameTime = SDL_GetTicks() - frameStart; // how long did it all take
    if (frameDelay > frameTime) {
      SDL_Delay(frameDelay - frameTime); // Delay as much as needed;
    }
    // performance temporary
    num_frames++;
    total_time += frameTime;
  }
  std::cout << "Time per frame = " << total_time / num_frames << "ms\n";
  g->clean();
  delete g;
  return 0;
}
