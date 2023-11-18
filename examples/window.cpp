#include "window.hpp"

#include <array>
#include <iostream>
#include <string>
#include <unordered_map>

#include "Input.hpp"
#include "ecs/component_manager.hpp"
#include "ecs/default_systems.hpp"
#include "engine.hpp"
#include "shader_manager.hpp"
#include "time.hpp"
#include "triangle.hpp"

int WindowTutorial() {
  Engine engine;
  Window window = Window::Make(engine, 640, 480, "ventana");
  while (!window.isDone()) {
    window.swap();
    engine.update();
  }
  return 0;
}

int TriangleTutorial() {
  Engine engine;
  Window window = Window::Make(engine, 640, 480, "ventana");

  //++++++++++++++++++++++++
  ComponentManager component_manager;
  Position pos(0.0f, 0.0f, 0.0f);
  ShaderManager shader_program =
      ShaderManager::MakeShaders("../assets/col.fs", "../assets/col.vs")
          .value();
  Render ren =
      Render::MakeTriangle(0.5f, Vec3(1.0f, 0.0f, 0.0f), shader_program);
  unsigned triangle = component_manager.addEntity<Position, Render>(pos, ren);
  //++++++++++++++++++++++++

  while (!window.isDone()) {
    //++++++++++++++++++++++++
    RenderSystem(component_manager.getAll<Position>(),
                 component_manager.getAll<Render>());
    //++++++++++++++++++++++++

    window.swap();
    engine.update();
  }

  return 0;
}

int main(int, char**) {
  // TODO: maybe we should use Engine::Make just for consistency with the window
  Engine engine;
  Window window = Window::Make(engine, 640, 480, "ventana");

  ComponentManager component_manager;
  Position pos(0.0f, 0.0f, 0.0f);
  // TODO: this should not be needed just an option
  // maybe we can use Engine to create some shader programs
  ShaderManager shader_program =
      ShaderManager::MakeShaders("../assets/col.fs", "../assets/col.vs")
          .value();
  Render ren =
      Render::MakeTriangle(0.5f, Vec3(1.0f, 0.0f, 0.0f), shader_program);
  unsigned triangle = component_manager.addEntity<Position, Render>(pos, ren);

  while (!window.isDone()) {
    // TODO: rename render System
    RenderSystem(component_manager.getAll<Position>(),
                 component_manager.getAll<Render>());

    // TODO: try to make this only one call
    window.swap();
    engine.update();
  }

  return 0;
}
