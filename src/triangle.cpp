#include "triangle.hpp"

#include "../src/stdafx.hpp"
#include "GL/glew.h"

Triangle::Triangle()
    : vertex_{{-0.5, -0.5, 0.0}, {0.0, 0.5, 0.0}, {0.5, -0.5, 0.0}},
      num_vertex_{3} {}

Triangle::~Triangle() {
  glDeleteVertexArrays(1, &vao_);
  glDeleteBuffers(1, &vbo_);
}

std::optional<Triangle> Triangle::Init() {

  std::optional<Triangle> res;

  glGenVertexArrays(1, res.vao());
  glGenBuffers(1, &vbo());

  glBindVertexArray(VAO_);

  auto a = sizeof(t.vertex_);

  glBindBuffer(GL_ARRAY_BUFFER, VBO_);
  glBufferData(GL_ARRAY_BUFFER, sizeof(t.vertex_), t.vertex_, GL_STATIC_DRAW);

  glVertexAttribPointer(0, t.num_vertex_, GL_FLOAT, GL_FALSE,
                        t.num_vertex_ * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);
}

void paint(Triangle& t, Window& w) {
  glBindVertexArray(t.vao());
  glDrawArrays(GL_TRIANGLES, 0, 3);
}