#pragma once

#include "../Utils/Constants.hpp"
#include "../Utils/Vec2.hpp"

class Transform {
 public:
  Vec2 position;
  int width = SPRITE_WIDTH;
  int height = SPRITE_WIDTH;
  Vec2 rotation;
  Vec2 scale;

  ~Transform() {}

  Transform(float xPos, float yPos, float xRot, float yRot, float xScale,
            float yScale, int height, int width) {
    this->position = Vec2(xPos, yPos);
    this->rotation = Vec2(xRot, yRot);
    this->scale = Vec2(xScale, yScale);
    this->height = height;
    this->width = width;
  }

  Transform(Vec2 &pos, Vec2 &rot, Vec2 &scl, int height = SPRITE_WIDTH,
            int width = SPRITE_HEIGHT) {
    this->position.x = pos.x;
    this->position.y = pos.y;
    this->rotation.x = rot.x;
    this->rotation.y = rot.y;
    this->scale.x = scl.x;
    this->scale.y = scl.y;
    this->height = height;
    this->width = width;
  }
};
