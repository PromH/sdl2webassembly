#include <entt/entt.hpp>
#include <iostream>

#include "Game.hpp"
#include "Components/Components.hpp"
#include "Utils/Vec2.hpp"
#include "Utils/Constants.hpp"
#include "Utils/GameObject.hpp"
#include "Utils/SpriteManager.hpp"

int frame = 0;
SDL_Renderer *Game::renderer = nullptr;
SDL_Event Game::event;
SDL_Rect Game::camera = {0, 0, GAME_SCREEN_WIDTH, GAME_SCREEN_HEIGHT};

entt::registry gameRegistry;

// GameObject *player;
entt::entity playerEntity;
SpriteManager* playerSprite;

bool Game::isRunning = false;

Game::Game()
{
  this->window = nullptr;
  this->renderer = nullptr;
  this->isRunning = false;
}

Game::~Game(){};

void Game::Init(const char *title, int xpos, int ypos, int width, int height,
                bool fullscreen)
{
  // Window and Renderer initialisations
  int flags = fullscreen ? SDL_WINDOW_FULLSCREEN : 0;

  if (SDL_Init(SDL_INIT_TIMER | SDL_INIT_VIDEO | SDL_INIT_AUDIO) == 0)
  {
    std::cout << "Subsystems initialised!" << std::endl;

    this->window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
    if (window)
    {
      std::cout << "Window created!" << std::endl;
    }
    else
    {
      std::cout << "Window not created!" << std::endl;
    }

    this->renderer = SDL_CreateRenderer(window, -1, 0);
    if (this->renderer)
    {
      SDL_SetRenderDrawColor(this->renderer, 255, 255, 255, 255);
      std::cout << "Renderer created!" << std::endl;
    }
    else
    {
      std::cout << "Renderer not created!" << std::endl;
    }

    this->isRunning = true;
  }
  else
  {
    std::cout << "Subsystems not initialised!" << std::endl;
    this->isRunning = false;
  }

  // Component initialisations
  if (this->isRunning)
  {
    // set up components here


    // player =
    //     new GameObject("./src/assets/sprites/player-default.png", 500, 500);

    playerEntity = gameRegistry.create();
    gameRegistry.emplace<Transform>(playerEntity, Vec2(500,500), Vec2(0,0), Vec2(2,2));
    gameRegistry.emplace<AnimationMap>(playerEntity);
    gameRegistry.emplace<Sprite>(playerEntity, "./src/assets/sprites/2d_animation_player-run.png");
    playerSprite = new SpriteManager(gameRegistry, playerEntity);
    playerSprite->AddAnimation(gameRegistry, "walk", Animation(0, 6, 100));
    playerSprite->Play(gameRegistry, "walk");
  }
}

void Game::HandleEvents()
{
  SDL_PollEvent(&event);
  switch (event.type)
  {
  case SDL_QUIT:
    Game::isRunning = false;
    break;
  default:
    break;
  }
}

void Game::Update()
{
  frame++;
  playerSprite->Update(gameRegistry);
}

void Game::Render()
{
  SDL_RenderClear(this->renderer);

  // Add things to render here
  playerSprite->Render(gameRegistry);

  SDL_RenderPresent(this->renderer);
}

void Game::Clean()
{
  SDL_DestroyWindow(this->window);
  SDL_DestroyRenderer(this->renderer);

  // delete player;
  delete playerSprite;

  SDL_Quit();
  std::cout << "Game cleaned!" << std::endl;
}
