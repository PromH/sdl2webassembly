#pragma once
#include <SDL.h>

class TextureManager {
 public:
  static SDL_Texture *LoadTexture(const char *textureFileName);
  static void Draw(SDL_Texture *tex, SDL_Rect src, SDL_Rect dest,
                   SDL_RendererFlip flip);
};
