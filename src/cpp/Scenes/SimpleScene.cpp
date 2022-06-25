#include "SimpleScene.hpp"

#include <spdlog/spdlog.h>

SimpleScene::SimpleScene() {}

SimpleScene::~SimpleScene() { this->Clean(); }

void SimpleScene::Init() {
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

  // Background Manager
  this->_background =
      std::make_unique<BackgroundManager>("", 1, Constants::TILE_WIDTH);
  this->_background->LoadBackground(Constants::GAME_SCREEN_WIDTH,
                                    Constants::GAME_SCREEN_HEIGHT);

  // Sprite manager for player
  this->_playerSprite =
      std::make_unique<SpriteManager>(this->_gameRegistry, this->_playerEntity);
  this->_playerSprite->AddAnimation(this->_gameRegistry, "walk",
                                    Animation(0, 6, 100));
  this->_playerSprite->Play(this->_gameRegistry, "walk");

  // Setting movement style
  this->_movementStyle = std::make_unique<SmoothMovementStyle>();
}

void SimpleScene::HandleEvents(SDL_Event* event) {
  this->HandlePlayerMovement(event);
}

void SimpleScene::Update() {
  this->_background->Update();
  this->_playerSprite->Update(this->_gameRegistry);
}

void SimpleScene::Render() {
  this->_background->Render();
  this->_playerSprite->Render(this->_gameRegistry);
}

void SimpleScene::Clean() {}

void SimpleScene::HandlePlayerMovement(SDL_Event* event) {
  if (!this->_gameRegistry.all_of<Transform, RigidBody>(this->_playerEntity)) {
    throw std::logic_error(this->_className +
                           " requires the following components from entity "
                           "to Update: RigidBody, and Transform");
  }

  Transform& transform =
      this->_gameRegistry.get<Transform>(this->_playerEntity);
  RigidBody& rigidBody =
      this->_gameRegistry.get<RigidBody>(this->_playerEntity);

  // Current states
  Vec2 currentPosition = transform.position;
  Vec2 targetPosition = transform.position;
  Vec2 velocity = rigidBody.velocity;
  SDL_RendererFlip spriteFlip = this->_playerSprite->spriteFlip;
  std::string animationToPlay = this->_playerSprite->key;

  // Events
  const Uint8* keyState = SDL_GetKeyboardState(NULL);
  if (keyState[SDL_SCANCODE_W]) {
    targetPosition = this->_movementStyle->GetNewPos(transform.position,
                                                     MovementDirection::UP);
  }
  if (keyState[SDL_SCANCODE_A]) {
    targetPosition = this->_movementStyle->GetNewPos(transform.position,
                                                     MovementDirection::LEFT);
    animationToPlay = "walk";
    spriteFlip = SDL_FLIP_HORIZONTAL;
  }
  if (keyState[SDL_SCANCODE_S]) {
    targetPosition = this->_movementStyle->GetNewPos(transform.position,
                                                     MovementDirection::DOWN);
    animationToPlay = "walk";
  }
  if (keyState[SDL_SCANCODE_D]) {
    targetPosition = this->_movementStyle->GetNewPos(transform.position,
                                                     MovementDirection::RIGHT);
    animationToPlay = "walk";
    spriteFlip = SDL_FLIP_NONE;
  }

  // Updating
  rigidBody.velocity =
      this->_movementStyle->CalculateVelocity(currentPosition, targetPosition);
  this->_playerSprite->spriteFlip = spriteFlip;
  this->_playerSprite->Play(this->_gameRegistry, animationToPlay.c_str());
  transform.position += rigidBody.velocity;

  // Resetting
  rigidBody.SetVelocity(0, 0);
}
