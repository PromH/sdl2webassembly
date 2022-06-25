#pragma once
#include <SDL.h>
#include <spdlog/spdlog.h>

#include "../Utils/TextureManager.hpp"
#include "../Utils/Vec2.hpp"

class Tile {
 public:
  SDL_Texture* texture;
  SDL_Rect srcRect, destRect;
  Vec2 position;

  Tile() = default;
  ~Tile() {
    spdlog::debug("Destroying tile!");
    SDL_DestroyTexture(this->texture);
  }

  Tile(int srcX, int srcY, int xPos, int yPos, int tsize, int tscale,
       const char* path) {
    this->texture = TextureManager::LoadTexture(path);

    this->position.x = xPos;
    this->position.y = yPos;

    this->srcRect.x = srcX;
    this->srcRect.y = srcY;
    this->srcRect.w = tsize;
    this->srcRect.h = tsize;

    this->destRect.x = xPos;
    this->destRect.y = yPos;
    this->destRect.w = tsize * tscale;
    this->destRect.h = tsize * tscale;
  }

  void Draw() {
    TextureManager::Draw(this->texture, this->srcRect, this->destRect,
                         SDL_FLIP_NONE);
  }
};
