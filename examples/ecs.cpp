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

struct ECSDummyComp {
  std::string a = "dummy";
};

void DummySystem(ComponentListCompact<ECSDummyComp>& a) {
  for (auto& [e, c] : a) {
    std::cout << c.a;
  }
}

int main(int, char**) {
  Engine e;
  Window window = Window::Make(e, 640, 480, "ventana");

  ShaderManager s =
      ShaderManager::MakeShaders("../assets/col.fs", "../assets/col.vs")
          .value();

  ComponentManager component_manager;
  component_manager.addComponentClass<ECSDummyComp>(
      ComponentListType::kCompact);

  Position pos;
  ECSDummyComp dummy;
  Render ren = Render::MakeTriangle(0.5f, {1.0f, 1.0f, 0.0f}, s);
  unsigned player = component_manager.addEntity<Position, Render, ECSDummyComp>(
      pos, ren, dummy);

  std::vector<unsigned int> ents;
  float trisize = 0.01f;
  float tridist = 0.02f;
  int width = 100;
  for (int y = 0; y < width; y++) {
    for (int x = 0; x < width; x++) {
      float pos_x = (x - ((float)width / 2.0f)) * tridist;
      float pos_y = (y - ((float)width / 2.0f)) * tridist;
      Position p(pos_x, pos_y, 0.0f);
      AI ai;
      Render r = Render::MakeTriangle(trisize, {1.0f, 1.0f, 0.0f}, s);
      ents.emplace_back(
          component_manager.addEntity<Position, AI, Render>(p, ai, r));
    }
  }

  InputManager i(window, inputMap);

  while (!window.isDone()) {
    // input
    float t_speed = 0.3f;
    Position* player_pos = component_manager.getComponent<Position>(player);
    if (i.buttonPressed("Up")) {
      player_pos->pos.y += t_speed * Time::DeltaTime();
    }
    if (i.buttonPressed("Down")) {
      player_pos->pos.y -= t_speed * Time::DeltaTime();
    }
    if (i.buttonPressed("Left")) {
      player_pos->pos.x -= t_speed * Time::DeltaTime();
    }
    if (i.buttonPressed("Right")) {
      player_pos->pos.x += t_speed * Time::DeltaTime();
    }


    DummySystem(component_manager.getCompactIterator<ECSDummyComp>());
    CircleMoveSystem(component_manager.getIterator<Position>(),
                     component_manager.getIterator<AI>());
    RenderSystem(component_manager.getAll<Position>(),
                 component_manager.getAll<Render>());

    window.update();
  }

  return 0;
}