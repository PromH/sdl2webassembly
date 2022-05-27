#include <SDL_image.h>

#include "TextureManager.hpp"
#include "../Game.hpp"


SDL_Texture *TextureManager::LoadTexture(const char *textureFileName)
{
  SDL_Surface *tempSurface = IMG_Load(textureFileName);
  SDL_Texture *tex = SDL_CreateTextureFromSurface(Game::renderer, tempSurface);
  SDL_FreeSurface(tempSurface);
  return tex;
}

void TextureManager::Draw(SDL_Texture *tex, SDL_Rect src, SDL_Rect dest,
                          SDL_RendererFlip flip)
{
  SDL_RenderCopyEx(Game::renderer, tex, &src, &dest, NULL, NULL, flip);
}
