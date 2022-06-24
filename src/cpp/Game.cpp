#include "Game.hpp"

#include <entt/entt.hpp>
#include <iostream>
#include <memory>

#include "Components/Components.hpp"
#include "Scenes/Scene.hpp"
#include "Scenes/SimpleScene.hpp"
#include "Utils/Constants.hpp"
#include "SpriteManager/SpriteManager.hpp"
#include "Utils/Vec2.hpp"

int frame = 0;
SDL_Renderer *Game::renderer = nullptr;
SDL_Event Game::event;
SDL_Rect Game::camera = {0, 0, GAME_SCREEN_WIDTH, GAME_SCREEN_HEIGHT};

std::unique_ptr<Scene> currentScene;

bool Game::isRunning = false;

Game::Game() {
  this->window = nullptr;
  this->renderer = nullptr;
  this->isRunning = false;
}

Game::~Game(){};

void Game::Init(const char *title, int xpos, int ypos, int width, int height,
                bool fullscreen) {
  // Window and Renderer initialisations
  int flags = fullscreen ? SDL_WINDOW_FULLSCREEN : 0;

  if (SDL_Init(SDL_INIT_TIMER | SDL_INIT_VIDEO | SDL_INIT_AUDIO) == 0) {
    std::cout << "Subsystems initialised!" << std::endl;

    this->window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
    if (window) {
      std::cout << "Window created!" << std::endl;
    } else {
      std::cout << "Window not created!" << std::endl;
    }

    this->renderer = SDL_CreateRenderer(window, -1, 0);
    if (this->renderer) {
      SDL_SetRenderDrawColor(this->renderer, 255, 255, 255, 255);
      std::cout << "Renderer created!" << std::endl;
    } else {
      std::cout << "Renderer not created!" << std::endl;
    }

    this->isRunning = true;
  } else {
    std::cout << "Subsystems not initialised!" << std::endl;
    this->isRunning = false;
  }

  // Component initialisations
  if (this->isRunning) {
    // set up scene here
    currentScene = std::make_unique<SimpleScene>();
    currentScene->Init();
  }
}

void Game::HandleEvents() {
  SDL_PollEvent(&this->event);
  switch (this->event.type) {
    case SDL_QUIT:
      Game::isRunning = false;
      break;
    default:
      break;
  }

  // Keyboard inputs
  if (this->event.type == SDL_KEYUP) {
    switch (this->event.key.keysym.sym) {
      case SDLK_ESCAPE:
        Game::isRunning = false;
      default:
        break;
    }
  }
  // Handle user inputs for the scene here
  currentScene->HandleEvents(&this->event);
}

void Game::Update() {
  frame++;

  // Update scene here
  currentScene->Update();
}

void Game::Render() {
  SDL_RenderClear(this->renderer);

  // Render scene here
  currentScene->Render();

  SDL_RenderPresent(this->renderer);
}

void Game::Clean() {
  SDL_DestroyWindow(this->window);
  SDL_DestroyRenderer(this->renderer);

  SDL_Quit();
  std::cout << "Game cleaned!" << std::endl;
}
