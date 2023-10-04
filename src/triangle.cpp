#include "triangle.hpp"
#include "window.hpp"
#include "../src/stdafx.hpp"

void paint(Triangle& t, Window& w) {

  glBindVertexArray(w.VAO_);
  glDrawArrays(GL_TRIANGLES, 0, 3);
  //glDisableVertexAttribArray(0);

}