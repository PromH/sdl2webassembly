#pragma once

#include <SDL.h>

#include <entt/entt.hpp>
#include <memory>
#include <string>

#include "../Components/Components.hpp"
#include "../MovementStyles/MovementStyle.hpp"
#include "../MovementStyles/SmoothMovementStyle.hpp"
#include "../Utils/Utils.hpp"
#include "Scene.hpp"

const std::string SPRITE_DIR_PATH = "./src/assets/sprites/";

class SimpleScene : public Scene {
 private:
  std::string _className = "SimpleScene";
  entt::registry _gameRegistry;
  entt::entity _playerEntity;
  std::unique_ptr<SpriteManager> _playerSprite;
  std::unique_ptr<MovementStyle> _movementStyle;

 public:
  SimpleScene();
  ~SimpleScene();
  void Init() override;
  void HandleEvents(SDL_Event* event) override;
  void Update() override;
  void Render() override;
  void Clean() override;
  void HandlePlayerMovement(SDL_Event* event);
};
