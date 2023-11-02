#include "ecs/component_manager.hpp"
#include "ecs/default_systems.hpp"
#include "engine.hpp"
#include "shader_manager.hpp"
#include "window.hpp"

int main(int, char**) {
  Engine e;
  auto w = Window::Make(e, 640, 480, "ventana");

  ComponentManager component_manager;
  unsigned player = component_manager.addTriangle(0.1f);

  std::vector<unsigned> ents;
  for (size_t y = 0; y < 10; y++) {
    for (size_t x = 0; x < 10; x++) {
      ents.emplace_back(component_manager.addTriangle(0.05f));
      Position p{Vec3(x * 0.1f - 0.5f, y * 0.1f - 0.5f, 0.0f)};
      AI ai;
      component_manager.setComponent(ents[x + y * 10], p);
      component_manager.setComponent(ents[x + y * 10], ai);
    }
  }

  ShaderManager s;
  s.generateAndCompileShader(kFragmentShader, "../assets/col.fs");
  s.generateAndCompileShader(kVertexShader, "../assets/col.vs");
  s.attachShaders();

  if (w) {
    auto& window = w.value();
    while (!window.isDone()) {
      CircleMoveSystem(component_manager.getAll<Position>(),
                       component_manager.getAll<AI>());
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