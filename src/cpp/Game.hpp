#pragma once

#define SDL_MAIN_HANDLED
#include <SDL.h>

// A class for rendering a SDL window containing a game.
class Game
{
private:
  SDL_Window *window;

public:
  Game();
  ~Game();

  void Init(const char *title, int xpos, int ypox, int width, int height,
            bool fullscreen = false);
  void HandleEvents();
  void Update();
  void Render();
  void Clean();

  static SDL_Renderer *renderer;
  static SDL_Event event;
  static bool isRunning;
  static SDL_Rect camera;
};
