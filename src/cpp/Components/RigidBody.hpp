#pragma once

#include "../Utils/Constants.hpp"
#include "../Utils/Vec2.hpp"

class RigidBody {
 public:
  Vec2 velocity;
  float mass = 1;
  float gravityScale = 0;

  ~RigidBody() {}
  RigidBody(Vec2 &velocity) {
    this->velocity.x = velocity.x;
    this->velocity.y = velocity.y;
  }

  void SetVelocity(float vx, float vy) {
    this->velocity.x = vx;
    this->velocity.y = vy;
  }
};
