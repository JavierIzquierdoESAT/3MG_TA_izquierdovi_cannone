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
    ShaderManager s =
        ShaderManager::MakeShaders("../assets/col.fs", "../assets/col.vs")
            .value();

    ComponentManager component_manager;
    unsigned player =
        component_manager.addTriangle(0.5f, &s, {1.0f, 0.0f, 0.0f});

    std::vector<unsigned> ents;
    float trisize = 0.01f;
    float tridist = 0.02f;
    int width = 100;
    for (int y = 0; y < width; y++) {
      for (int x = 0; x < width; x++) {
        float pos_x = (x - ((float)width / 2.0f)) * tridist;
        float pos_y = (y - ((float)width / 2.0f)) * tridist;
        ents.emplace_back(component_manager.addTriangle(trisize, &s, {0.0f, 1.0f, 0.0f}));
        Position p{Vec3(pos_x, pos_y, 0.0f)};
        AI ai;
        component_manager.setComponent(ents[x + y * width], p);
        component_manager.setComponent(ents[x + y * width], ai);
      }
    }

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

      s.useProgram();
      window.swap();
      // end frame;
      e.update();
    }
  }
  return 0;
}