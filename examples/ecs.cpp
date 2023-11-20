#include "ecs/component_manager.hpp"
#include "ecs/default_systems.hpp"
#include "engine.hpp"
#include "input.hpp"
#include "shader_manager.hpp"
#include "time.hpp"
#include "window.hpp"

InputButtonMap inputMap{
    {"1Up", {InputButton::W}},      {"1Down", {InputButton::S}},
    {"1Left", {InputButton::A}},    {"1Right", {InputButton::D}},

    {"2Up", {InputButton::UP}},     {"2Down", {InputButton::DOWN}},
    {"2Left", {InputButton::LEFT}}, {"2Right", {InputButton::RIGHT}},

    {"3Up", {InputButton::I}},      {"3Down", {InputButton::K}},
    {"3Left", {InputButton::J}},    {"3Right", {InputButton::L}},

    {"4Up", {InputButton::KP_8}},   {"4Down", {InputButton::KP_5}},
    {"4Left", {InputButton::KP_4}}, {"4Right", {InputButton::KP_6}},
};

struct InputMovement {
  std::vector<std::string> actions;
};

struct Movement {
  coma::Vec2 dir = coma::Vec2(0.0f, 0.0f);
  float speed = 0.3f;
};

void InputMoveSystem(ComponentListCompact<Movement>& mov,
                     ComponentListCompact<InputMovement>& input,
                     const InputManager& i) {
  for (auto& [e, icmp] : input) {
    auto mcmp_it = mov.at(e);
    if (mcmp_it != mov.end()) {
      auto& mcmp = mcmp_it->second;
      mcmp.dir = coma::Vec2(0.0f, 0.0f);
      int count = 0;
      for (const std::string& action : icmp.actions) {
        if (i.buttonPressed(action)) {
          switch (count) {
            case 0:
              mcmp.dir.y++;
              break;
            case 1:
              mcmp.dir.y--;
              break;
            case 2:
              mcmp.dir.x--;
              break;
            case 3:
              mcmp.dir.x++;
              break;
            default:
              break;
          }
        }
        count++;
      }
    }
  }
}

void MoveSystem(ComponentList<Position>& pos,
                ComponentListCompact<Movement>& mov) {
  for (auto& [e, mcmp] : mov) {
    if (pos.at(e)->has_value()) {
      Position& pcmp = pos.at(e)->value();
      coma::Vec3 dir = coma::Vec3(mcmp.dir.x, mcmp.dir.y, 0.0f);
      dir *= (mcmp.speed * Time::DeltaTime());
      pcmp.pos += dir;
    }
  }
}

unsigned createPlayer(coma::Vec3 pos, std::vector<std::string> input,
                      ShaderManager& s, ComponentManager& component_manager) {
  Position poss;
  poss.pos = pos;
  InputMovement inputt{input};
  Movement move;
  Render ren = Render::MakeTriangle(0.3f, {1.0f, 1.0f, 0.0f}, s);
  return component_manager.addEntity<Position, Render, InputMovement, Movement>(
      poss, ren, inputt, move);
}

int main(int, char**) {
  Engine e;
  Window window = Window::Make(e, 640, 480, "ventana");

  ShaderManager s =
      ShaderManager::MakeShaders("../assets/col.fs", "../assets/col.vs")
          .value();

  ComponentManager component_manager;
  component_manager.addComponentClass<InputMovement>(
      ComponentListType::kCompact);
  component_manager.addComponentClass<Movement>(ComponentListType::kCompact);

  unsigned p1 =
      createPlayer(coma::Vec3(-0.5f, +0.5f, 0.0f),
                   {"1Up", "1Down", "1Left", "1Right"}, s, component_manager);
  //unsigned p2 =
      createPlayer(coma::Vec3(+0.5f, +0.5f, 0.0f),
                   {"2Up", "2Down", "2Left", "2Right"}, s, component_manager);
  
  component_manager.deleteEntity(p1);

  //unsigned p3 =
      createPlayer(coma::Vec3(-0.5f, -0.5f, 0.0f),
                   {"3Up", "3Down", "3Left", "3Right"}, s, component_manager);
  //unsigned p4 =
      createPlayer(coma::Vec3(+0.5f, -0.5f, 0.0f),
                   {"4Up", "4Down", "4Left", "4Right"}, s, component_manager);
   p1 =
      createPlayer(coma::Vec3(-0.5f, +0.5f, 0.0f),
                   {"1Up", "1Down", "1Left", "1Right"}, s, component_manager);

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
    // float t_speed = 0.3f;
    // Position* player_pos = component_manager.getComponent<Position>(player);
    // if (i.buttonPressed("Up")) {
    //  player_pos->pos.y += t_speed * Time::DeltaTime();
    //}
    // if (i.buttonPressed("Down")) {
    //  player_pos->pos.y -= t_speed * Time::DeltaTime();
    //}
    // if (i.buttonPressed("Left")) {
    //  player_pos->pos.x -= t_speed * Time::DeltaTime();
    //}
    // if (i.buttonPressed("Right")) {
    //  player_pos->pos.x += t_speed * Time::DeltaTime();
    //}

    InputMoveSystem(component_manager.getCompactIterator<Movement>(),
                    component_manager.getCompactIterator<InputMovement>(), i);
    MoveSystem(component_manager.getIterator<Position>(),
               component_manager.getCompactIterator<Movement>());
    CircleMoveSystem(component_manager.getIterator<Position>(),
                     component_manager.getIterator<AI>());
    RenderSystem(component_manager.getAll<Position>(),
                 component_manager.getAll<Render>());

    window.update();
  }

  return 0;
}