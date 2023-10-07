#include "window.hpp"

#include "GL/glew.h"
#include "engine.hpp"
#include "shader_manager.hpp"
#include "triangle.hpp"

int main(int, char**) {
  Engine e;

  auto w = Window::Make(e, 640, 480, "ventana");

  ShaderManager sm;

  Triangle t;

  t.init();

  ShaderManager s;

  s.generateAndCompileShader(kFragmentShader, "../assets/col.fs");
  s.generateAndCompileShader(kVertexShader, "../assets/col.vs");

  s.atachShaders();


  if (w) {
    auto& window = w.value();

    while (!window.isDone()) {

       
      s.useProgram();
      paint(t);
     
      window.swap();
    }
  }

  return 0;
}
