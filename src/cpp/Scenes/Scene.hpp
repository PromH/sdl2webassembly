#pragma once
#include <SDL.h>

class Scene {
 public:
  virtual void Init(){};
  virtual void HandleEvents(SDL_Event* event){};
  virtual void Update(){};
  virtual void Render(){};
  virtual void Clean(){};
};
