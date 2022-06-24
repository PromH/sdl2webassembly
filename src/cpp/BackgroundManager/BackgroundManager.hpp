#pragma once
#include <vector>
#include <string>

#include "Tile.hpp"

class BackgroundManager {
private:
  std::string _backgroundFilePath;
  int _backgroundScale;
	int _tileSize;
	int _scaledSize;
  std::vector<Tile> _tiles;

public:
  BackgroundManager(const char* bgFile, int bgScale, int tSize);
  ~BackgroundManager();
  void LoadBackground(int width, int height);
  void AddTile(int srcX, int srcY, int xPos, int yPos);
  void Update();
  void Render();
};
