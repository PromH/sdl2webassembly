#pragma once
#include <SDL.h>
#include <map>

#include "../Utils/Constants.hpp"
#include "../Utils/Vec2.hpp"
#include "../Utils/TextureManager.hpp"

#include "Animation.hpp"
#include "Transform.hpp"

class Sprite
{
public:
  SDL_Texture *texture;
  SDL_Rect srcRect, destRect;

  Sprite() = default;
  virtual ~Sprite()
  {
    SDL_DestroyTexture(this->texture);
  }

  virtual void Update(Transform *transform) {}
  virtual void Play(const char *key) {}
};

class StaticSprite : Sprite
{
public:
  ~StaticSprite() {}

  StaticSprite(const char *textureSheet, SDL_Rect srcRect, SDL_Rect destRect)
  {
    this->texture = TextureManager::LoadTexture(textureSheet);
    this->srcRect = srcRect;
    this->destRect = destRect;
  }
};

class AnimatedSprite : Sprite
{
public:
  bool animated = false;
  int frames = 0;
  int animIdx = 0;
  std::map<const char *, Animation> animations;
  int speed = FRAME_DELAY;

  ~AnimatedSprite() {}

  AnimatedSprite(const char *textureSheet, SDL_Rect srcRect, SDL_Rect destRect, bool isAnimated)
  {
    this->texture = TextureManager::LoadTexture(textureSheet);
    this->animated = isAnimated;

    this->srcRect = srcRect;
    this->destRect = destRect;
  }

  void Update(Transform *transform) override
  {
    if (animated)
    {
      this->srcRect.x = srcRect.w * static_cast<int>((SDL_GetTicks() / this->speed) % this->frames);
    }
    this->srcRect.y = this->animIdx * transform->height;
  }

  void Play(const char *key) override
  {
    if (this->animations.count(key))
    {
      this->frames = this->animations[key].frames;
      this->animIdx = this->animations[key].index;
      this->speed = this->animations[key].speed;
    }
  }

  void AddAnimation(const char *key, Animation animation)
  {
    this->animations.emplace(key, animation);
  }
};
