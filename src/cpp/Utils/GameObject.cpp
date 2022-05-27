#include <iostream>

#include "GameObject.hpp"
#include "Constants.hpp"
#include "TextureManager.hpp"

const int SCALE_FACTOR = 2 * SPRITE_SCALE;

GameObject::GameObject(const char *textureSheet, int x, int y) {
  this->_objTexture = TextureManager::LoadTexture(textureSheet);
  this->_xPos = x;
  this->_yPos = y;
  this->_destRect = SDL_Rect();
  this->_srcRect = SDL_Rect();
}

GameObject::~GameObject() {}

void GameObject::Update(int x, int y) {
  this->_srcRect.h = SPRITE_HEIGHT;
  this->_srcRect.w = SPRITE_WIDTH;
  this->_srcRect.x = 0;
  this->_srcRect.y = 0;

  this->_destRect.x = x;
  this->_destRect.y = y;
  this->_destRect.w = this->_srcRect.w * SCALE_FACTOR;
  this->_destRect.h = this->_srcRect.h * SCALE_FACTOR;
}

void GameObject::Render() {
  SDL_RenderCopy(Game::renderer, this->_objTexture, &(this->_srcRect),
                 &(this->_destRect));
}
