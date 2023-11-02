#include "ecs/component_manager.hpp"
#include "ecs/default_systems.hpp"

#include "engine.hpp"
#include "window.hpp"
#include "shader_manager.hpp"



int main(int, char**) {

  Engine e;
  auto w = Window::Make(e, 640, 480, "ventana");

  ComponentManager component_manager;
  unsigned player = component_manager.addTriangle();

  ShaderManager s;
  s.generateAndCompileShader(kFragmentShader, "../assets/col.fs");
  s.generateAndCompileShader(kVertexShader, "../assets/col.vs");
  s.attachShaders();

  if (w) {
    auto& window = w.value();
    while (!window.isDone()) {

      render_system(component_manager.getAll<Position>(),
                    component_manager.getAll<Render>());


      s.useProgram();
      window.swap();
      // end frame;
      e.update();
    }
  }
  return 0;
}