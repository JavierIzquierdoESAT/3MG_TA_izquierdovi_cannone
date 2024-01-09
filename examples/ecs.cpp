#include "ecs/component_manager.hpp"
#include "ecs/default_systems.hpp"
#include "engine.hpp"
#include "input.hpp"
#include "shader_manager.hpp"
#include "time.hpp"
#include "window.hpp"

///---------------------TimeTests-----------------------------------
struct CompactTest1 {
  float a = 0;
};
struct CompactTest2 {
  float a = 0;
};
struct SparseTest1 {
  float a = 0;
};
struct SparseTest2 {
  float a = 0;
};
void CompactHard(ComponentListCompact<CompactTest1>& c1,
                 ComponentListCompact<CompactTest2>& c2) {
  auto start = std::chrono::system_clock::now();
  for (auto& [e, icmp] : c1) {
    auto mcmp_it = c2.at(e);
    if (mcmp_it != c2.end()) {
      auto& mcmp = mcmp_it->second;
      mcmp.a = 0.0f;
    }
  }
  auto end = std::chrono::system_clock::now();
  std::chrono::nanoseconds elapsed = end - start;
  std::cout << elapsed.count() << " : Compact Hard" << '\n';
}
void CompactEasy(ComponentListCompact<CompactTest1>& c1,
                 ComponentListCompact<CompactTest2>& c2) {
  auto start = std::chrono::system_clock::now();
  ComponentIterator it(c1, c2);
  while (it.next()) {
    auto [pv, aiv] = it.get();
    pv.a = 0.0f;
    aiv.a = 0.0f;
  }
  auto end = std::chrono::system_clock::now();
  std::chrono::nanoseconds elapsed = end - start;
  std::cout << elapsed.count() << " : Compact Easy" << '\n';
}
void MixedEasy(ComponentListCompact<CompactTest1>& c1,
               ComponentListSparse<SparseTest1>& c2) {
  auto start = std::chrono::system_clock::now();
  ComponentIterator it(c1, c2);
  while (it.next()) {
    auto [pv, aiv] = it.get();
    pv.a = 0.0f;
    aiv.a = 0.0f;
  }
  auto end = std::chrono::system_clock::now();
  std::chrono::nanoseconds elapsed = end - start;
  std::cout << elapsed.count() << " : Mixed Easy" << '\n';
}
void MixedHard(ComponentListCompact<CompactTest1>& c1,
               ComponentListSparse<SparseTest1>& c2) {
  auto start = std::chrono::system_clock::now();
  for (auto& [e, mcmp] : c1) {
    if (c2.at(e)->has_value()) {
      auto& pcmp = c2.at(e)->value();
      pcmp.a = 0.0f;
    }
  }
  auto end = std::chrono::system_clock::now();
  std::chrono::nanoseconds elapsed = end - start;
  std::cout << elapsed.count() << " : Mixed Hard" << '\n';
}
void SparseEasy(ComponentListSparse<SparseTest1>& c1,
                ComponentListSparse<SparseTest2>& c2) {
  auto start = std::chrono::system_clock::now();
  ComponentIterator it(c1, c2);
  while (it.next()) {
    auto [pv, aiv] = it.get();
    pv.a = 0.0f;
    aiv.a = 0.0f;
  }
  auto end = std::chrono::system_clock::now();
  std::chrono::nanoseconds elapsed = end - start;
  std::cout << elapsed.count() << " : Sparse Easy" << '\n';
}
void SparseHard(ComponentListSparse<SparseTest1>& c1,
                ComponentListSparse<SparseTest2>& c2) {
  auto start = std::chrono::system_clock::now();
  auto p_it = c1.begin();
  auto ai_it = c2.begin();
  for (; p_it != c1.end() && ai_it != c2.end(); ++p_it, ++ai_it) {
    if (!p_it->has_value() || !ai_it->has_value()) continue;
    auto& pv = p_it->value();
    auto& aiv = ai_it->value();
    pv.a = 0.0f;
    aiv.a = 0.0f;
  }
  auto end = std::chrono::system_clock::now();
  std::chrono::nanoseconds elapsed = end - start;
  std::cout << elapsed.count() << " : Sparse Hard" << '\n';
}
///---------------------TimeTests-----------------------------------


InputButtonMap g_input_map{
  {"1Up", {InputButton::W}}, {"1Down", {InputButton::S}},
  {"1Left", {InputButton::A}}, {"1Right", {InputButton::D}},

  {"2Up", {InputButton::UP}}, {"2Down", {InputButton::DOWN}},
  {"2Left", {InputButton::LEFT}}, {"2Right", {InputButton::RIGHT}},

  {"3Up", {InputButton::I}}, {"3Down", {InputButton::K}},
  {"3Left", {InputButton::J}}, {"3Right", {InputButton::L}},

  {"4Up", {InputButton::KP_8}}, {"4Down", {InputButton::KP_5}},
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
  ComponentIterator it(mov, input);
  while (it.next()) {
    auto [mcmp, icmp] = it.get();
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

void MoveSystem(ComponentListSparse<Position>& pos,
                ComponentListCompact<Movement>& mov) {
  ComponentIterator it(mov, pos);
  while (it.next()) {
    auto [mcmp, pcmp] = it.get();
    coma::Vec3 dir = coma::Vec3(mcmp.dir.x, mcmp.dir.y, 0.0f);
    dir *= (mcmp.speed * Time::DeltaTime());
    pcmp.pos += dir;
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


int defaultMain() {
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

  int width = 100;
  for (int y = 0; y < width; y++) {
    for (int x = 0; x < width; x++) {
      float trisize = 0.01f;
      float tridist = 0.02f;
      float pos_x = (x - ((float)width / 2.0f)) * tridist;
      float pos_y = (y - ((float)width / 2.0f)) * tridist;
      Position p(pos_x, pos_y, 0.0f);
      AI ai;
      Render r = Render::MakeTriangle(trisize, {1.0f, 1.0f, 0.0f}, s);
      ents.emplace_back(
          component_manager.addEntity<Position, AI, Render>(p, ai, r));
    }
  }

  InputManager i(window, g_input_map);

  while (!window.isDone()) {
    InputMoveSystem(component_manager.getCompactList<Movement>(),
                    component_manager.getCompactList<InputMovement>(), i);
    MoveSystem(component_manager.getSparseList<Position>(),
               component_manager.getCompactList<Movement>());
    CircleMoveSystem(component_manager.getSparseList<Position>(),
                     component_manager.getSparseList<AI>());
    RenderSystem(component_manager.getSparseList<Position>(),
                 component_manager.getSparseList<Render>());
    window.update();
  }

  return 0;
}

int TimeMain() {
  Engine e;
  Window window = Window::Make(e, 640, 480, "ventana");

  ShaderManager s =
      ShaderManager::MakeShaders("../assets/col.fs", "../assets/col.vs")
      .value();

  ComponentManager component_manager;
  component_manager.addComponentClass<CompactTest1>(
      ComponentListType::kCompact);
  component_manager.addComponentClass<CompactTest2>(
      ComponentListType::kCompact);
  component_manager.addComponentClass<SparseTest1>(
      ComponentListType::kSparse);
  component_manager.addComponentClass<SparseTest2>(
      ComponentListType::kSparse);


  for (size_t i = 0; i < 100000; i++) {
    std::srand(1);
    auto r = std::rand();
    auto en = component_manager.addEntity();
    if ((i + r) % 2 != 0) {
      SparseTest1 st1;
      component_manager.setComponent(en, st1);
      SparseTest2 st2;
      component_manager.setComponent(en, st2);
    }

    if ((i + r) % 2 == 0) {
      SparseTest1 st1;
      component_manager.setComponent(en, st1);
    }
    if ((i + r) % 4 == 0 || (i + r) % 2 != 0) {
      SparseTest2 st2;
      component_manager.setComponent(en, st2);
    }
    if ((i + r) % 6 == 0) {
      CompactTest1 ct1;
      component_manager.setComponent(en, ct1);
    }
    if ((i + r) % 8 == 0 || (i + r) % 2 != 0) {
      CompactTest2 ct2;
      component_manager.setComponent(en, ct2);
    }
  }

  while (!window.isDone()) {
    CompactHard(component_manager.getCompactList<CompactTest1>(),
                component_manager.getCompactList<CompactTest2>());
    CompactEasy(component_manager.getCompactList<CompactTest1>(),
                component_manager.getCompactList<CompactTest2>());

    MixedHard(component_manager.getCompactList<CompactTest1>(),
              component_manager.getSparseList<SparseTest1>());
    MixedEasy(component_manager.getCompactList<CompactTest1>(),
              component_manager.getSparseList<SparseTest1>());


    SparseHard(component_manager.getSparseList<SparseTest1>(),
               component_manager.getSparseList<SparseTest2>());
    SparseEasy(component_manager.getSparseList<SparseTest1>(),
               component_manager.getSparseList<SparseTest2>());

    window.update();
  }

  return 0;
}

int main(int, char**) {
  defaultMain();
  //TimeMain();
  return 0;
}
