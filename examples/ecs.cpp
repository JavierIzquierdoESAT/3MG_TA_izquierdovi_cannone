#include "ecs/component_manager.hpp"
#include "ecs/default_systems.hpp"
#include "engine.hpp"
#include "input.hpp"
#include "shader_manager.hpp"
#include "time.hpp"
#include "window.hpp"

InputButtonMap inputMap{
    {"Up", {InputButton::W}},
    {"Down", {InputButton::S}},
    {"Left", {InputButton::A}},
    {"Right", {InputButton::D}},
};

int main(int, char**) {
  Engine e;
  auto w = Window::Make(e, 640, 480, "ventana");
  if (w) {
    auto& window = w.value();
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

    std::optional<ShaderManager> s =
        ShaderManager::MakeShaders("../assets/col.fs", "../assets/col.vs");
    float f[3] = {0.0f, 1.0f, 0.0f};
    s->setUniformValue(DataType::FLOAT_3, f, "initialUniform");
    InputManager i = window.addInputManager(inputMap);

    while (!window.isDone()) {
      // input
      float t_speed = 0.3f;
      Position* player_pos = component_manager.getComponent<Position>(player);
      if (i.buttonPressed("Up")) {
        player_pos->pos.y += t_speed * Time::delta_time();
      }
      if (i.buttonPressed("Down")) {
        player_pos->pos.y -= t_speed * Time::delta_time();
      }
      if (i.buttonPressed("Left")) {
        player_pos->pos.x -= t_speed * Time::delta_time();
      }
      if (i.buttonPressed("Right")) {
        player_pos->pos.x += t_speed * Time::delta_time();
      }

      CircleMoveSystem(component_manager.getAll<Position>(),
                       component_manager.getAll<AI>());
      render_system(component_manager.getAll<Position>(),
                    component_manager.getAll<Render>());

      s->useProgram();
      window.swap();
      // end frame;
      e.update();
    }
  }
  return 0;
}