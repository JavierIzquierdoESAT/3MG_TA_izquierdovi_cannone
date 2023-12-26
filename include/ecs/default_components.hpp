#pragma once

#include <array>
#include <vector>

#include "buffer.hpp"
#include "math/vector_2.h"
#include "math/vector_3.h"
#include "shader_manager.hpp"

///@brief Component storing position in world
struct Position {
  Position() : pos{coma::Vec3(0, 0, 0)} {}
  Position(float x, float y, float z) : pos{coma::Vec3(x, y, z)} {}

  Position(const Position& p):
  pos{p.pos} {
    std::cout<<"huh?";
  }

  /// @brief current position in world
  coma::Vec3 pos;
};

/// @brief Component used for performing automated movement
struct AI {
  /// @brief iterations moved in the same direction
  unsigned counter = 0;
  /// @brief direction currently moving to
  bool right = false;
};

/// @brief Component storing rendering information
struct Render {
  // TODO: rendermode
  Render(std::vector<coma::Vec3> position, std::vector<coma::Vec3> normals,
         std::vector<coma::Vec3> colors, std::vector<coma::Vec2> uvs,
         std::vector<short int> index, ShaderManager& sm)
      : shaderProgram{sm},
        buffer(position, normals, colors, uvs),
        index_buffer(
            static_cast<void*>(index.data()),
            static_cast<unsigned int>(index.size() * sizeof(short int))) {}

  static Render MakeTriangle(float size, coma::Vec3 color, ShaderManager& sm) {
    return Render(
        {{-size, -size, 0.0f}, {0.0f, size, 0.0f}, {size, -size, 0.0f}},
        {{1.0f, 1.0f, 1.0f}, {1.0f, 1.0f, 1.0f}, {1.0f, 1.0f, 1.0f}},
        {color, {0.0f, 1.0f, 0.0f}, {0.0f, 0.0f, 1.0f}},
        {{0, 0}, {0, 0}, {0, 0}}, {0, 1, 2}, sm);
  }

  Render(Render&&) = default;
  Render& operator=(const Render&& other) noexcept {
    shaderProgram = other.shaderProgram;

    // TODO: possible bug I would still need the buffer move
    return *this;
  };

  /// @brief shaders to use while renderign this entity
  class ShaderManager& shaderProgram;
  /// @brief GPU buffer storing vertex positions, normals and uvs
  Buffer buffer;
  /// @brief GPU buffer containing the order in which to paint the vercices
  Buffer index_buffer;
};