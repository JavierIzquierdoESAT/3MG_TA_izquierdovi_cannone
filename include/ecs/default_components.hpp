#pragma once

#include <array>
#include <vector>

#include "buffer.hpp"
#include "math/vector_2.h"
#include "math/vector_3.h"
#include "shader_manager.hpp"

struct Position {
  Vec3 pos = Vec3(0.0f);
};

struct AI {
  unsigned counter = 0;
  bool right = false;
};

struct Render {
  // TODO: rendermode
  Render(std::vector<Vec3> position, std::vector<Vec3> normals,
         std::vector<Vec3> colors, std::vector<Vec2> uvs, ShaderManager* sm)
      : pos{position},
        normal{normals},
        color{colors},
        uv{uvs},
        shaderProgram{sm},
        buffer{Buffer(position, normals, colors, uvs)} {
  }

  // TODO: posibly useless to store
  class ShaderManager* shaderProgram;
  std::vector<Vec3> pos;
  std::vector<Vec3> normal;
  std::vector<Vec3> color;
  std::vector<Vec2> uv;

  Buffer buffer;
};