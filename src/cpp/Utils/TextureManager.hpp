#pragma once
#include <SDL.h>

#include <vector>

class TextureManager {
 public:
  static SDL_Texture *LoadTexture(const char *textureFileName);
  static void Draw(SDL_Texture *tex, SDL_Rect src, SDL_Rect dest,
                   SDL_RendererFlip flip);
  static SDL_Texture *RenderTexturesToTexture(
      std::vector<SDL_Texture *> textures, std::vector<SDL_Rect *> srcs,
      std::vector<SDL_Rect *> dests, std::vector<SDL_RendererFlip> flips, int w,
      int h);
  static void DrawNoRects(SDL_Texture *tex, SDL_RendererFlip flip);
};
