#pragma once

#include <array>
#include <vector>

#include "buffer.hpp"
#include "math/vector_2.h"
#include "math/vector_3.h"
#include "math/matrix_4.h"
#include "shader_manager.hpp"

struct Position {
  Position() : pos{coma::Vec3(0, 0, 0)} {}
  Position(float x, float y, float z) : pos{coma::Vec3(x, y, z)} {}

  coma::Vec3 pos;
};

struct AI {
  unsigned counter = 0;
  bool right = false;
};

struct Material {
  Buffer mesh;    // will be Mesh class
  Buffer indices; // will be Index class

  //probably handled with bitmasks
  bool is_visible;
  bool is_transparent;

  std::array<Material*, 4> children;

  //Transform* t;
};
struct Transform {
  //coma::Vec3 position = {0.0f, 0.0f, 0.0f};
  //coma::Vec3 Rotation = {0.0f, 0.0f, 0.0f};
  //coma::Vec3 Scale = {1.0f, 1.0f, 1.0f};

  coma::Mat4 t;
};

struct Render {
  // TODO: rendermode
  Render(std::vector<coma::Vec3> position, std::vector<coma::Vec3> normals,
         std::vector<coma::Vec3> colors, std::vector<coma::Vec2> uvs,
         ShaderManager& sm)
      : pos{position},
        normal{normals},
        color{colors},
        uv{uvs},
        shaderProgram{sm},
        buffer(position, normals, colors, uvs) {}

  static Render MakeTriangle(float size, coma::Vec3 color, ShaderManager& sm) {
    return Render(
        {{-size, -size, 0.0f}, {0.0f, size, 0.0f}, {size, -size, 0.0f}},
        {{1.0f, 1.0f, 1.0f}, {1.0f, 1.0f, 1.0f}, {1.0f, 1.0f, 1.0f}},
        {color, {0.0f, 1.0f, 0.0f}, {0.0f, 0.0f, 1.0f}},
        {{0, 0}, {0, 0}, {0, 0}}, sm);
  }

  Render(Render&&) = default;
  Render& operator=(const Render&& other) noexcept { 
    shaderProgram = other.shaderProgram;
    pos = other.pos;
    normal = other.normal;
    color = other.color;
    uv = other.uv;
    //TODO: possible bug I would still need the buffer move
    return *this; 
};

  // TODO: posibly useless to store
  class ShaderManager& shaderProgram;
  std::vector<coma::Vec3> pos;
  std::vector<coma::Vec3> normal;
  std::vector<coma::Vec3> color;
  std::vector<coma::Vec2> uv;

  Buffer buffer;
};