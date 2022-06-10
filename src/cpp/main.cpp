#include <SDL.h>
#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif
#include <stdlib.h>

#include <functional>
#include <iostream>
#include <memory>

#include "Game.hpp"
#include "Utils/Constants.hpp"

// Types
using VoidCallback = std::function<void()>;

// Globals
std::shared_ptr<Game> game = nullptr;

// Constants
const int fps = GAME_FPS;
const int frameDelay = 1000 / fps;

void RunGame() {
  Uint32 frameStart = SDL_GetTicks();

  // handle any user input
  game->HandleEvents();

  // update all objects e.g. positions, etc.
  game->Update();

  // render changes to the display
  game->Render();

  // Limiting framerate
  int frameTime = SDL_GetTicks() - frameStart;
  if (frameDelay > frameTime) {
    SDL_Delay(frameDelay - frameTime);
  }
}

int main(int argc, const char *argv[]) {
  // Game Object Setup
  // SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "2");
  game = std::make_shared<Game>();
  game->Init("MyGame", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
             GAME_SCREEN_WIDTH, GAME_SCREEN_HEIGHT);
  bool gameIsRunning = true;

// Game Loop
#ifdef __EMSCRIPTEN__
  emscripten_set_main_loop(RunGame, 0, 1);
#else
  while (gameIsRunning) {
    RunGame();
  }
#endif

  // Cleanup
  game->Clean();

  return 0;
}
