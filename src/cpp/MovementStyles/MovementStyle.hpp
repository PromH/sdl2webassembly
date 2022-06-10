#pragma once
#include <iostream>

#include "../Utils/Utils.hpp"

enum MovementDirection { UP = 1, DOWN = 2, LEFT = 3, RIGHT = 4 };

/** Interface that provides the next position  */
class MovementStyle {
 public:
  virtual Vec2 GetNewPos(Vec2 &pos, MovementDirection direction) {
    return pos;
  };

  Vec2 CalculateVelocity(Vec2 &origin, Vec2 &target) {
    Vec2 velocity = Vec2(0, 0);

    // X
    if (origin.x < target.x) {
      velocity.x = 1 * PLAYER_MOVEMENT_SPEED;
    } else if (origin.x > target.x) {
      velocity.x = -1 * PLAYER_MOVEMENT_SPEED;
    } else {
      velocity.x = 0;
    }

    // Y
    if (origin.y < target.y) {
      velocity.y = 1 * PLAYER_MOVEMENT_SPEED;
    } else if (origin.y > target.y) {
      velocity.y = -1 * PLAYER_MOVEMENT_SPEED;
    } else {
      velocity.y = 0;
    }

    return velocity;
  };
};
