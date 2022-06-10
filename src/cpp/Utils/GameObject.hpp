#pragma once
#include <SDL.h>

class GameObject {
 private:
  int _xPos;
  int _yPos;
  SDL_Texture *_objTexture;
  SDL_Rect _srcRect, _destRect;

 public:
  GameObject(const char *textureSheet, int x = 0, int y = 0);
  ~GameObject();

  void Update(int x, int y);
  void Render();
};
