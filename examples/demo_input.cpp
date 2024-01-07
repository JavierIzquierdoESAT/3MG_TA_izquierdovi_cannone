#include <string>
#include <unordered_map>

#include "Input.hpp"
#include "ecs/component_manager.hpp"
#include "ecs/default_systems.hpp"
#include "engine.hpp"
#include "shader_manager.hpp"
#include "time.hpp"
#include "window.hpp"

using namespace coma;

InputButtonMap g_input_map{
    {"Up", {InputButton::W, InputButton::UP}},
    {"Down", {InputButton::S, InputButton::DOWN}},
    {"Left", {InputButton::A, InputButton::LEFT}},
    {"Right", {InputButton::D, InputButton::RIGHT}},
};

int main(int, char**) {
  Engine engine;
  Window window = Window::Make(engine, 640, 480, "ventana");
  InputManager input(window, g_input_map);

  ComponentManager component_manager;
  Position pos(0.0f, 0.0f, 0.0f);
  ShaderManager shader_program =
      ShaderManager::MakeShaders("../assets/col.fs", "../assets/col.vs")
          .value();
  Render ren =
      Render::MakeTriangle(0.5f, Vec3(1.0f, 0.0f, 0.0f), shader_program);
  unsigned triangle = component_manager.addEntity<Position, Render>(pos, ren);

  while (!window.isDone()) {
    float speed = 0.3f;
    Position* trianglePos = component_manager.getComponent<Position>(triangle);
    if (input.buttonPressed("Up")) {
      trianglePos->pos.y += speed * Time::DeltaTime();
    }
    if (input.buttonPressed("Down")) {
      trianglePos->pos.y -= speed * Time::DeltaTime();
    }
    if (input.buttonPressed("Left")) {
      trianglePos->pos.x -= speed * Time::DeltaTime();
    }
    if (input.buttonPressed("Right")) {
      trianglePos->pos.x += speed * Time::DeltaTime();
    }

    RenderSystem(component_manager.getSparseList<Position>(),
                 component_manager.getSparseList<Render>());

    window.update();
  }

  return 0;
}
