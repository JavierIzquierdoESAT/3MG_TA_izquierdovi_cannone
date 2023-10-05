#include "triangle.hpp"

#include "../src/stdafx.hpp"
#include "buffer.hpp"

Triangle::Triangle()
    : vertex_{{-0.5, -0.5, 0.0, 1.0, 0.0, 0.0},
              {0.0, 0.5, 0.0, 0.0, 1.0, 0.0},
              {0.5, -0.5, 0.0, 0.0, 0.0, 1.0}},
      num_vertex_{3} {}

Triangle::~Triangle() {}

void Triangle::init() {
  data_buffer_.initWithData(vertex_, sizeof(vertex_));

  data_buffer_.enableVertexArray(num_vertex_, num_vertex_ * sizeof(float), 0);
}

Buffer Triangle::data_buffer() const { return data_buffer_; }

const float* Triangle::color(int p) const { return &vertex_[p].colors_.x; }

void paint(Triangle& t) {
  t.data_buffer().bindVertexArray();

  glDrawArrays(GL_TRIANGLES, 0, 3);
}