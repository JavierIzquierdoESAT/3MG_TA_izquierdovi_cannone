#include "triangle.hpp"

#include "../src/stdafx.hpp"

Triangle::Triangle()
    : vertex_{ {{-0.5, -0.5, 0.0}, {0.0, 0.0, 0.0},{1.0f,0.0f,0.0f},{0,0}},
              {{0.0, 0.5, 0.0}, {0.0, 0.0, 0.0},{0.0f,1.0f,0.0f}, {0,0}},
              {{0.5, -0.5, 0.0}, {0.0, 0.0, 0.0},{0.0f,0.0f,1.0f}, {0,0}}},
      num_vertex_{3},
      data_buffer_{Buffer(vertex_, sizeof(vertex_))} {
    data_buffer_.enableVertexArray(0, num_vertex_, 11 * sizeof(float), 0);
    data_buffer_.enableVertexArray(1, num_vertex_, 11 * sizeof(float), 12);
    data_buffer_.enableVertexArray(1, num_vertex_, 11 * sizeof(float), 24);
    data_buffer_.enableVertexArray(1, num_vertex_, 11 * sizeof(float), 36);
    data_buffer_.bindVertexArray();
}

Triangle::~Triangle() {}

Buffer Triangle::data_buffer() const { 
  return Buffer(0,0);
}

void Triangle::updateBuffers() {
  data_buffer_.uploadData(&vertex_, sizeof(vertex_), 0);
  data_buffer_.enableVertexArray(0, num_vertex_, 11 * sizeof(float), 0);
  data_buffer_.enableVertexArray(1, num_vertex_, 11 * sizeof(float), 12);
  data_buffer_.enableVertexArray(1, num_vertex_, 11 * sizeof(float), 24);
  data_buffer_.enableVertexArray(1, num_vertex_, 11 * sizeof(float), 36);
  data_buffer_.bindVertexArray();
}

void paint(Triangle&) { glDrawArrays(GL_TRIANGLES, 0, 3); }