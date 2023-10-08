#include "triangle.hpp"

#include "../src/stdafx.hpp"

Triangle::Triangle()
    : vertex_{{-0.5, -0.5, 0.0, 1.0, 0.0, 0.0},
              {0.0, 0.5, 0.0, 0.0, 1.0, 0.0},
              {0.5, -0.5, 0.0, 0.0, 0.0, 1.0}},
      num_vertex_{3},
      data_buffer_{Buffer(vertex_, sizeof(vertex_))} {
  // TODO: this is initializing Buffer not following RAII
  data_buffer_.enableVertexArray(num_vertex_, num_vertex_ * sizeof(float), 0);
}

Triangle::~Triangle() {}

Buffer Triangle::data_buffer() const { return data_buffer_; }

void Triangle::updateBuffers() {
  data_buffer_.reset(vertex_, sizeof(vertex_));
  Buffer b = Buffer(vertex_, sizeof(vertex_));
  b.enableVertexArray(num_vertex_, num_vertex_ * sizeof(float), 0);
  data_buffer_ = b;
}

void paint(Triangle& t) {
  t.data_buffer().bindVertexArray();

  glDrawArrays(GL_TRIANGLES, 0, 3);
}