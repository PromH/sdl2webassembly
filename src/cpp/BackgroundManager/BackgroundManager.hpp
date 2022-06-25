#pragma once
#include <SDL.h>
#include <SDL_image.h>

#include <memory>
#include <string>
#include <vector>

#include "Tile.hpp"

class BackgroundManager {
 private:
  std::string _backgroundFilePath;
  int _backgroundScale;
  int _tileSize;
  int _scaledSize;
  std::vector<std::unique_ptr<Tile>> _tiles;
  std::vector<SDL_Texture*> _tileTextures;
  std::vector<SDL_Rect*> _tileSrcs;
  std::vector<SDL_Rect*> _tileDests;
  std::vector<SDL_RendererFlip> _tileFlips;
  SDL_Texture* _texture;
  SDL_Rect _srcRect;
  SDL_Rect _destRect;

 public:
  BackgroundManager(const char* bgFile, int bgScale, int tSize);
  ~BackgroundManager();
  void LoadBackground(int width, int height);
  void AddTile(int srcX, int srcY, int xPos, int yPos);
  void Update();
  void Render();
};
