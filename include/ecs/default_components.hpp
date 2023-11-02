#pragma once

#include <vector>

#include "math/vector_2.h"
#include "math/vector_3.h"

struct Position {
  Vec3 pos;
};

struct Render {
  // TODO: rendermode
  // TODO: shaderprogram
  std::vector<Vec3> pos;
  std::vector<Vec3> normal;
  std::vector<Vec3> color;
  std::vector<Vec2> uv;
};