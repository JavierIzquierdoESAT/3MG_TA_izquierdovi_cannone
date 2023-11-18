#pragma once

#include <array>
#include <vector>

#include "buffer.hpp"
#include "math/vector_2.h"
#include "math/vector_3.h"
#include "shader_manager.hpp"

struct Position {
  Position() : pos{Vec3(0, 0, 0)} {}
  Position(float x, float y, float z) : pos{Vec3(x, y, z)} {}

  Vec3 pos;
};

struct AI {
  unsigned counter = 0;
  bool right = false;
};

struct Render {
  // TODO: rendermode
  Render(std::vector<Vec3> position, std::vector<Vec3> normals,
         std::vector<Vec3> colors, std::vector<Vec2> uvs, ShaderManager& sm)
      : pos{position},
        normal{normals},
        color{colors},
        uv{uvs},
        shaderProgram{sm},
        buffer(position, normals, colors, uvs) {}

  static Render MakeTriangle(float size, Vec3 color, ShaderManager& sm) {
    return Render(
        {{-size, -size, 0.0f}, {0.0f, size, 0.0f}, {size, -size, 0.0f}},
        {{1.0f, 1.0f, 1.0f}, {1.0f, 1.0f, 1.0f}, {1.0f, 1.0f, 1.0f}},
        {color, {0.0f, 1.0f, 0.0f}, {0.0f, 0.0f, 1.0f}},
        {{0, 0}, {0, 0}, {0, 0}}, sm);
  }

  Render(Render&&) = default;

  Render& operator=(const Render& other) {}
  // TODO: posibly useless to store
  class ShaderManager& shaderProgram;
  std::vector<Vec3> pos;
  std::vector<Vec3> normal;
  std::vector<Vec3> color;
  std::vector<Vec2> uv;

  Buffer buffer;
};