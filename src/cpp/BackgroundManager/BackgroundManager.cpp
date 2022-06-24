#include "BackgroundManager.hpp"
#include <spdlog/spdlog.h>

BackgroundManager::BackgroundManager(const char* bgFile, int bgScale, int tSize) {
  this->_backgroundFilePath = bgFile;
  this->_backgroundScale = bgScale;
  this->_tileSize = tSize;
  this->_scaledSize = bgScale * tSize;
}

BackgroundManager::~BackgroundManager() {}

void BackgroundManager::LoadBackground(int width, int height) {
  int numRows = width / this->_tileSize;
  int numCols = height / this->_tileSize;
  for (int i=0; i<numRows; i+=1) {
    for (int j=0; j<numCols; j+=1) {
      spdlog::debug("tile{},{} is drawing at ({},{})", i, j, i * this->_tileSize, j * this->_tileSize);
      this->AddTile(0, 0, i * this->_tileSize, j * this->_tileSize);
    }
  }
}

void BackgroundManager::AddTile(int srcX, int srcY, int xPos, int yPos) {
  std::string tilePath = "./src/assets/background/tiles/grid.png";
  if ((xPos > 760  && yPos > 600)) {
    tilePath = "./src/assets/background/tiles/grid2.png";
  }
  this->_tiles.emplace_back(srcX, srcY, xPos, yPos, this->_tileSize, this->_backgroundScale, tilePath.c_str());
}

void BackgroundManager::Update() {}

void BackgroundManager::Render() {
  std::string tilePath = "./src/assets/background/tiles/grid2.png";
  auto a_tile = Tile(0, 0, 1, 1, this->_tileSize, this->_backgroundScale, tilePath.c_str());
  a_tile.Draw();
  for (int i=0; i<this->_tiles.size(); i+=1) {
    this->_tiles[i].Draw();
  }
}
