#pragma once

class Scene {
 public:
  virtual void Init(){};
  virtual void HandleEvents(){};
  virtual void Update(){};
  virtual void Render(){};
  virtual void Clean(){};
};
