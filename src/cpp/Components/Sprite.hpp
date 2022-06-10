#pragma once
#include <SDL.h>

#include <entt/entt.hpp>
#include <exception>
#include <map>
#include <stdexcept>

#include "../Utils/Constants.hpp"
#include "../Utils/TextureManager.hpp"
#include "../Utils/Vec2.hpp"
#include "Animation.hpp"
#include "Transform.hpp"

class Sprite {
 public:
  SDL_Texture *texture;
  SDL_Rect srcRect, destRect;

  ~Sprite() { SDL_DestroyTexture(this->texture); }

  Sprite(const char *textureSheet) {
    this->texture = TextureManager::LoadTexture(textureSheet);
  }
};
