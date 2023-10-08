#include "triangle.hpp"

#include "../src/stdafx.hpp"
#include "buffer.hpp"

Triangle::Triangle()
    : vertex_{{-0.5, -0.5, 0.0, 1.0, 0.0, 0.0},
              {0.0, 0.5, 0.0, 0.0, 1.0, 0.0},
              {0.5, -0.5, 0.0, 0.0, 0.0, 1.0}},
      num_vertex_{3},
      data_buffer_{Buffer(vertex_, sizeof(vertex_))} {
  data_buffer_.enableVertexArray(num_vertex_, num_vertex_ * sizeof(float), 0);
}

Triangle::~Triangle() {}

Buffer Triangle::data_buffer() const { return data_buffer_; }

void paint(Triangle& t) {
  t.data_buffer().bindVertexArray();

  glDrawArrays(GL_TRIANGLES, 0, 3);
}