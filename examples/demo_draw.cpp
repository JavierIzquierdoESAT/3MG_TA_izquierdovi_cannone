#include "ecs/component_manager.hpp"
#include "ecs/default_systems.hpp"
#include "engine.hpp"
#include "shader_manager.hpp"
#include "time.hpp"
#include "window.hpp"

using namespace coma;

int main(int, char**) {
  Engine engine;
  Window window = Window::Make(engine, 640, 480, "ventana");

  ComponentManager component_manager;
  Position pos(0.0f, 0.0f, 0.0f);
  ShaderManager shader_program =
      ShaderManager::MakeShaders("../assets/col.fs", "../assets/col.vs")
          .value();
  Render ren =
      Render::MakeTriangle(0.5f, Vec3(1.0f, 0.0f, 0.0f), shader_program);
  unsigned triangle = component_manager.addEntity<Position, Render>(pos, ren);

  while (!window.isDone()) {
    RenderSystem(component_manager.getAll<Position>(),
                 component_manager.getAll<Render>());

    window.update();
  }

  return 0;
}
