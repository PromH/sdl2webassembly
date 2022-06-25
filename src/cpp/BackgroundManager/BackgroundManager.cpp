#include "BackgroundManager.hpp"

#include <spdlog/spdlog.h>

#include "../Game.hpp"
#include "../Utils/Constants.hpp"

BackgroundManager::BackgroundManager(const char* bgFile, int bgScale,
                                     int tSize) {
  this->_backgroundFilePath = bgFile;
  this->_backgroundScale = bgScale;
  this->_tileSize = tSize;
  this->_scaledSize = bgScale * tSize;
}

BackgroundManager::~BackgroundManager() { SDL_DestroyTexture(this->_texture); }

void BackgroundManager::LoadBackground(int width, int height) {
  int numRows = width / this->_tileSize;
  int numCols = height / this->_tileSize;
  for (int i = 0; i < numRows; i += 1) {
    for (int j = 0; j < numCols; j += 1) {
      this->AddTile(0, 0, i * this->_tileSize, j * this->_tileSize);
    }
  }
}

void BackgroundManager::AddTile(int srcX, int srcY, int xPos, int yPos) {
  std::string tilePath = "./src/assets/background/tiles/grid.png";
  this->_tiles.push_back(std::make_unique<Tile>(
      srcX, srcY, xPos, yPos, Constants::TILE_WIDTH, 1, tilePath.c_str()));
}

void BackgroundManager::Update() {}

void BackgroundManager::Render() {
  for (int i = 0; i < this->_tiles.size(); i += 1) {
    this->_tiles[i]->Draw();
  }
}
