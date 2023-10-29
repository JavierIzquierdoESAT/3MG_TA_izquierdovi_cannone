#include "triangle.hpp"

#include "../src/stdafx.hpp"

Triangle::Triangle()
    : vertex_{{{-0.5, -0.5, 0.0}, {1.0, 0.0, 0.0}},
              {{0.0, 0.5, 0.0}, {0.0, 1.0, 0.0}},
              {{0.5, -0.5, 0.0}, {0.0, 0.0, 1.0}}},
      num_vertex_{3},
      data_buffer_{Buffer(vertex_, sizeof(vertex_))} {
  // TODO: this is initializing Buffer not following RAII
    data_buffer_.enableVertexArray(0, num_vertex_, 6 * sizeof(float), 0);
    data_buffer_.enableVertexArray(1,num_vertex_, 6 * sizeof(float), 12);
    data_buffer_.bindVertexArray();
}

Triangle::~Triangle() {}

Buffer Triangle::data_buffer() const { return data_buffer_; }

void Triangle::updateBuffers() {
  data_buffer_.uploadData(&vertex_, sizeof(vertex_), 0);
  data_buffer_.enableVertexArray(0, num_vertex_, 6 * sizeof(float), 0);
  data_buffer_.enableVertexArray(1, num_vertex_, 6 * sizeof(float), 12);
  data_buffer_.bindVertexArray();
}

void paint(Triangle& t) { glDrawArrays(GL_TRIANGLES, 0, 3); }