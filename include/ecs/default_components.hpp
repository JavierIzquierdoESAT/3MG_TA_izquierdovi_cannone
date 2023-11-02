#pragma once

#include <vector>
#include <array>

#include "buffer.hpp"
#include "math/vector_2.h"
#include "math/vector_3.h"

struct Position {
  Vec3 pos = Vec3(0.0f);
};

struct AI {
  unsigned counter = 0;
  bool right = false;
};

struct Render {
  // TODO: rendermode
  // TODO: shaderprogram
  Render(std::vector<Vec3> position, std::vector<Vec3> normals,
         std::vector<Vec3> colors, std::vector<Vec2> uvs)
      : pos{position},
        normal{normals},
        color{colors},
        uv{uvs},
        buffer{Buffer(position, normals, colors, uvs)} {
  }

//TODO: posibly useless to store
  std::vector<Vec3> pos;
  std::vector<Vec3> normal;
  std::vector<Vec3> color;
  std::vector<Vec2> uv;

  Buffer buffer;
};