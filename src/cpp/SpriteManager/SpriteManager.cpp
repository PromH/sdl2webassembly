#include "SpriteManager.hpp"

#include <string.h>

#include <exception>
#include <iostream>
#include <stdexcept>
#include <string>

#include "../Components/Components.hpp"
#include "../Utils/TextureManager.hpp"

SpriteManager::SpriteManager(entt::registry &registry, entt::entity entity) {
  this->entity = entity;

  // Initialise Sprite
  if (!registry.all_of<Transform, Sprite>(this->entity)) {
    throw std::logic_error(this->_className +
                           " requires the following components from entity to "
                           "Update: Sprite, and Transform");
  }

  Transform &transform = registry.get<Transform>(this->entity);
  Sprite &sprite = registry.get<Sprite>(this->entity);

  sprite.srcRect.x = 0;
  sprite.srcRect.y = 0;
  sprite.srcRect.w = transform.width;
  sprite.srcRect.h = transform.height;
}

SpriteManager::~SpriteManager() {}

void SpriteManager::Update(entt::registry &registry) {
  if (!registry.all_of<Transform, Sprite, RigidBody>(this->entity)) {
    throw std::logic_error(this->_className +
                           " requires the following components from entity to "
                           "Update: Sprite, RigidBody, and Transform");
  }

  Transform &transform = registry.get<Transform>(this->entity);
  Sprite &sprite = registry.get<Sprite>(this->entity);
  RigidBody &rigidBody = registry.get<RigidBody>(this->entity);

  // animated
  if (registry.all_of<AnimationMap>(this->entity) &&
      strcmp(this->key, "") != 0) {
    AnimationMap &animationMap = registry.get<AnimationMap>(this->entity);
    int speed = animationMap.animations[this->key].speed;
    int index = animationMap.animations[this->key].index;
    int frames = animationMap.animations[this->key].frames;
    sprite.srcRect.x =
        sprite.srcRect.w * static_cast<int>((SDL_GetTicks() / speed) % frames);
    sprite.srcRect.y = index * transform.height;
  }

  sprite.destRect.x = static_cast<int>(transform.position.x);
  sprite.destRect.y = static_cast<int>(transform.position.y);
  sprite.destRect.w = transform.scale.x * transform.width;
  sprite.destRect.h = transform.scale.y * transform.height;
}

void SpriteManager::Render(entt::registry &registry) {
  if (!registry.all_of<Sprite>(this->entity)) {
    throw std::logic_error(this->_className +
                           " requires the following components from entity to "
                           "Draw: Sprite, and Transform");
  }

  Sprite &sprite = registry.get<Sprite>(this->entity);
  TextureManager::Draw(sprite.texture, sprite.srcRect, sprite.destRect,
                       this->spriteFlip);
}

void SpriteManager::Play(entt::registry &registry, const char *key) {
  if (registry.all_of<AnimationMap>(this->entity) &&
      (registry.get<AnimationMap>(this->entity)).animations.count(key)) {
    this->key = key;
  } else {
    std::invalid_argument(
        std::string(key) +
        " does not exist for entity's AnimationMap component");
  }
}

void SpriteManager::AddAnimation(entt::registry &registry, const char *key,
                                 Animation animation) {
  if (registry.all_of<AnimationMap>(this->entity)) {
    AnimationMap &animationMap = registry.get<AnimationMap>(this->entity);
    animationMap.animations.emplace(key, animation);
  } else {
    std::invalid_argument(
        std::string(key) +
        " does not exist for entity's AnimationMap component");
  }
}
