#include "window.hpp"
#include "engine.hpp"
#include "shader_manager.hpp"
#include "triangle.hpp"

#include "GL/glew.h"

int main(int, char**) {

  Engine e;

  auto w = Window::Make(e,640,480,"ventana");

  ShaderManager sm;

  Triangle t;



  t.vertex_[0] = { -1.0f, -1.0f, 0.0f };
  t.vertex_[1] = { 1.0f, -1.0f, 0.0f };
  t.vertex_[2] = { 0.0f, 1.0f, 0.0f };

  

  if (w) {
    auto& window = w.value();
    e.initShaders();
    window.initBuffers(t);
    while (!window.isDone())
    {
      
        paint(t, window);

        window.swap();
    }
  }

  return 0;
}



