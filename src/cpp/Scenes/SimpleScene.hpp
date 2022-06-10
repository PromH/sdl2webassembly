#pragma once

#include <SDL.h>

#include <entt/entt.hpp>
#include <iostream>
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
  SDL_Event _event;
  entt::registry _gameRegistry;
  entt::entity _playerEntity;
  std::unique_ptr<SpriteManager> _playerSprite;
  std::unique_ptr<MovementStyle> _movementStyle;

 public:
  void Init() override {
    this->_playerEntity = this->_gameRegistry.create();

    // Components for player
    auto initialPlayerPosition = Vec2(500, 500);
    auto initialPlayerRotation = Vec2(0, 0);
    auto initialPlayerScale = Vec2(2, 2);
    auto initialPlayerVelocity = Vec2(0, 0);
    this->_gameRegistry.emplace<Transform>(
        this->_playerEntity, initialPlayerPosition, initialPlayerRotation,
        initialPlayerScale);
    this->_gameRegistry.emplace<RigidBody>(this->_playerEntity,
                                           initialPlayerVelocity);
    this->_gameRegistry.emplace<AnimationMap>(this->_playerEntity);
    this->_gameRegistry.emplace<Sprite>(
        this->_playerEntity,
        (SPRITE_DIR_PATH + "2d_animation_player-run.png").c_str());

    // Sprite manager for player
    this->_playerSprite = std::make_unique<SpriteManager>(this->_gameRegistry,
                                                          this->_playerEntity);
    this->_playerSprite->AddAnimation(this->_gameRegistry, "walk",
                                      Animation(0, 6, 100));
    this->_playerSprite->Play(this->_gameRegistry, "walk");

    // Setting movement style
    this->_movementStyle = std::make_unique<SmoothMovementStyle>();
  }

  void HandleEvents() override {
    SDL_PollEvent(&this->_event);
    this->HandlePlayerMovement();
  }

  void Update() override { this->_playerSprite->Update(this->_gameRegistry); }

  void Render() override { this->_playerSprite->Render(this->_gameRegistry); }

  void Clean() override {}

  void HandlePlayerMovement() {
    if (!this->_gameRegistry.all_of<Transform, RigidBody>(
            this->_playerEntity)) {
      throw std::logic_error(this->_className +
                             " requires the following components from entity "
                             "to Update: RigidBody, and Transform");
    }

    Transform &transform =
        this->_gameRegistry.get<Transform>(this->_playerEntity);
    RigidBody &rigidBody =
        this->_gameRegistry.get<RigidBody>(this->_playerEntity);

    if (this->_event.type == SDL_KEYDOWN) {
      Vec2 currentPosition = transform.position;
      Vec2 targetPosition = transform.position;

      switch (this->_event.key.keysym.sym) {
        case SDLK_w:
          targetPosition = this->_movementStyle->GetNewPos(
              transform.position, MovementDirection::UP);
          break;
        case SDLK_a:
          targetPosition = this->_movementStyle->GetNewPos(
              transform.position, MovementDirection::LEFT);
          this->_playerSprite->Play(this->_gameRegistry, "walk");
          this->_playerSprite->spriteFlip = SDL_FLIP_HORIZONTAL;
          break;
        case SDLK_s:
          targetPosition = this->_movementStyle->GetNewPos(
              transform.position, MovementDirection::DOWN);
          this->_playerSprite->Play(this->_gameRegistry, "walk");
          break;
        case SDLK_d:
          targetPosition = this->_movementStyle->GetNewPos(
              transform.position, MovementDirection::RIGHT);
          this->_playerSprite->Play(this->_gameRegistry, "walk");
          break;
        default:
          break;
      }

      // Updating velocity
      rigidBody.velocity = this->_movementStyle->CalculateVelocity(
          currentPosition, targetPosition);
      
      // Updating position
      transform.position += rigidBody.velocity;
    }

    if (this->_event.type == SDL_KEYUP) {
      switch (this->_event.key.keysym.sym) {
        case SDLK_w:
          rigidBody.velocity.y = 0;
          break;
        case SDLK_a:
          rigidBody.velocity.x = 0;
          this->_playerSprite->spriteFlip = SDL_FLIP_NONE;
          break;
        case SDLK_s:
          rigidBody.velocity.y = 0;
          break;
        case SDLK_d:
          rigidBody.velocity.x = 0;
          break;
        default:
          break;
      }
    }
  }

  SimpleScene() {}

  ~SimpleScene() { this->Clean(); }
};
