#pragma once
#include "buffer.hpp"
#include "math/vector_3.h"
#include "math/vector_2.h"

struct Vertex {
  coma::Vec3 position_;
  coma::Vec3 normal_;
  coma::Vec3 colors_;
  coma::Vec2 uv_;
  // Vec3 normal_;
};

class Triangle {
 public:
  Triangle();
  ~Triangle();

  Buffer data_buffer() const;

  void set_color_(coma::Vec3 color) {
    vertex_[2].colors_ = color;
  }

  void move(coma::Vec3 pos) {
    for (int i = 0; i < 3; i++) {
      vertex_[i].position_.x += pos.x;
      vertex_[i].position_.y += pos.y;
      vertex_[i].position_.z += pos.z;
    }
  }
  void set_position_(coma::Vec3 pos) {
    for (int i = 0; i < 3; i++) {
      vertex_[i].position_ = pos;
    }
  }

  void updateBuffers();

 private:
  const int num_vertex_ = 3;
  Vertex vertex_[3];
  Buffer data_buffer_;
};

void paint(Triangle& t);