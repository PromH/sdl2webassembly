#pragma once

#include "../Utils/Utils.hpp"
#include "MovementStyle.hpp"

class SmoothMovementStyle : public MovementStyle {
 public:
  ~SmoothMovementStyle() {}
  SmoothMovementStyle() {}

  Vec2 GetNewPos(Vec2 &pos, MovementDirection direction) override {
    Vec2 delta = Vec2(0, 0);
    switch (direction) {
      case MovementDirection::UP:
        delta.y = -1;
        break;
      case MovementDirection::DOWN:
        delta.y = 1;
        break;
      case MovementDirection::LEFT:
        delta.x = -1;
        break;
      case MovementDirection::RIGHT:
        delta.x = 1;
        break;
      default:
        break;
    }
    return pos + delta;
  };
};
