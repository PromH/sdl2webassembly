#include "TextureManager.hpp"

#include <SDL_image.h>

#include "../Game.hpp"

SDL_Texture *TextureManager::LoadTexture(const char *textureFileName) {
  SDL_Surface *tempSurface = IMG_Load(textureFileName);
  SDL_Texture *tex = SDL_CreateTextureFromSurface(Game::renderer, tempSurface);
  SDL_FreeSurface(tempSurface);
  return tex;
}

void TextureManager::Draw(SDL_Texture *tex, SDL_Rect src, SDL_Rect dest,
                          SDL_RendererFlip flip) {
  SDL_RenderCopyEx(Game::renderer, tex, &src, &dest, NULL, NULL, flip);
}

SDL_Texture *TextureManager::RenderTexturesToTexture(
    std::vector<SDL_Texture *> textures, std::vector<SDL_Rect *> srcs,
    std::vector<SDL_Rect *> dests, std::vector<SDL_RendererFlip> flips, int w,
    int h) {
  SDL_Texture *tex = SDL_CreateTexture(Game::renderer, SDL_PIXELFORMAT_RGBA8888,
                                       SDL_TEXTUREACCESS_TARGET, w, h);

  // Changing target
  SDL_SetRenderTarget(Game::renderer, tex);
  SDL_RenderClear(Game::renderer);

  // Rendering to texture
  for (int i = 0; i < textures.size(); i += 1) {
    SDL_RenderCopyEx(Game::renderer, textures[i], srcs[i], dests[i], NULL, NULL,
                     flips[i]);
  }

  // Detaching and returning
  SDL_SetRenderTarget(Game::renderer, NULL);
  return tex;
}

void TextureManager::DrawNoRects(SDL_Texture *tex, SDL_RendererFlip flip) {
  SDL_RenderCopyEx(Game::renderer, tex, NULL, NULL, NULL, NULL, flip);
}
