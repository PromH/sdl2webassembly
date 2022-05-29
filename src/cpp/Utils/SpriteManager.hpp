#pragma once
#include <SDL.h>
#include <entt/entt.hpp>

#include "../Components/Animation.hpp"

class SpriteManager
{
private:
  std::string _className = "SpriteManager";

public:
  entt::entity entity;
  const char* key = "";
  SDL_RendererFlip spriteFlip = SDL_FLIP_NONE;

  SpriteManager(entt::registry& registry, entt::entity entity);
  ~SpriteManager();

  void Update(entt::registry& registry);
  void Render(entt::registry& registry);
  void Play(entt::registry& registry, const char* key);
  void AddAnimation(entt::registry& registry, const char* key, Animation animation);
};
