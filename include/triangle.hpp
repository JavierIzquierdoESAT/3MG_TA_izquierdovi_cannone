#pragma once
#include "buffer.hpp"

struct Vec3 {
  float x, y, z;
};

struct Vertex {
  Vec3 position_;
  Vec3 colors_;
  // Vec3 normal_;
};

class Triangle {
 public:
  Triangle();
  ~Triangle();

  Buffer data_buffer() const;

 private:
  const int num_vertex_ = 3;
  Vertex vertex_[3];
  Buffer data_buffer_;
};

void paint(Triangle& t);