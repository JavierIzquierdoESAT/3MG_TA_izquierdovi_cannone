
#include <optional>
#include <vector>

#include "Input.hpp"
#include "buffer.hpp"
#include "ecs/component_manager.hpp"
#include "ecs/default_systems.hpp"
#include "engine.hpp"
#include "jobsystem.hpp"
#include "load_obj.hpp"
#include "math/vector_3.h"
#include "shader_manager.hpp"
#include "time.hpp"
#include "window.hpp"

using namespace coma;

InputButtonMap g_input_map{
    {"Up", {InputButton::W, InputButton::UP}},
    {"Down", {InputButton::S, InputButton::DOWN}},
    {"Left", {InputButton::A, InputButton::LEFT}},
    {"Right", {InputButton::D, InputButton::RIGHT}},
    {"RotateLeft", {InputButton::Q}},
    {"RotateRight", {InputButton::E}},
};

int main(int, char**) {
  Engine engine;
  Window window = Window::Make(engine, 640, 480, "ventana");
  InputManager input(window, g_input_map);
  ComponentManager component_manager;
  ShaderManager shader_manager =
      ShaderManager::MakeShaders("../assets/Shaders/obj.fs",
                                 "../assets/Shaders/obj.vs")
          .value();
  engine.loadObj("../assets/obj/pollo.obj");
  engine.loadObj("../assets/obj/stool.obj");
  engine.loadObj("../assets/obj/sword_shield.obj");
  engine.loadObj("../assets/obj/torch.obj");
  std::vector<Mesh> m = engine.waitMeshLoad();

  std::vector<Render> render_components;
  // add the meshes of the OBJ to the ecs
  Position p[4] = {{0.0f, 0.0f, 0.0f}, {0, 0, 15}, {0, 0, 15}, {0, -5.5, 15}};
  Scale s[4] = {{1.0f, 1.0f, 1.0f},
                {1.0f, 1.0f, 1.0f},
                {1.0f, 1.0f, 1.0f},
                {1.0f, 1.0f, 1.0f}};
  Rotation r[4] = {{0.0f, 0.0f, 0.0f},
                   {0.0f, 0.0f, 0.0f},
                   {0.0f, 0.0f, 0.0f},
                   {0.0f, 0.0f, 0.0f}};
  unsigned int movible_e = 0;
  for (size_t x = 0; x < m.size(); x++) {
    render_components = m[x].createBuffers(shader_manager);
    for (auto& render_cmp : render_components) {
      movible_e =
          component_manager.addEntity<Position, Scale, Rotation, Render>(
              p[x], s[x], r[x], render_cmp);
    }
  }

  // creating obj grid
  int width = 50;
  for (int y = 0; y < width; y++) {
    for (int x = 0; x < width; x++) {
      float tridist = 1.0f;
      float pos_x =
          (static_cast<float>(x) - static_cast<float>(width) / 2.0f) * tridist;
      float pos_y =
          (static_cast<float>(y) - static_cast<float>(width) / 2.0f) * tridist;
      Position posi(pos_x, pos_y, 0.0f);
      Scale scal(1.0f, 1.0f, 1.0f);
      Rotation rot(0.0f, 0.0f, 0.0f);
      AI aia;
      render_components = m[0].createBuffers(shader_manager);
      for (auto& render_cmp : render_components) {
        component_manager.addEntity<Position, Scale, Rotation, AI, Render>(
            posi, scal, rot, aia, render_cmp);
      }
    }
  }

  float elapsed_time = 0;
  while (!window.isDone()) {

    shader_manager.setUniformValue(DataType::FLOAT_1, &elapsed_time, "time");
    float speed = 2.5f;
    Position* triangle_pos =
        component_manager.getComponent<Position>(2);
    Rotation* triangle_rot =
    component_manager.getComponent<Rotation>(2);
    if (input.buttonPressed("Up")) {
      triangle_pos->pos.y += speed * Time::DeltaTime();
    }
    if (input.buttonPressed("Down")) {
      triangle_pos->pos.y -= speed * Time::DeltaTime();
    }
    if (input.buttonPressed("Left")) {
      triangle_pos->pos.x -= speed * Time::DeltaTime();
    }
    if (input.buttonPressed("Right")) {
      triangle_pos->pos.x += speed * Time::DeltaTime();
    }

    if (input.buttonPressed("RotateLeft")) {
      triangle_rot->rot.y += speed * Time::DeltaTime();
    }

    if (input.buttonPressed("RotateRight")) {
      triangle_rot->rot.y -= speed * Time::DeltaTime();
    }

    // render the obj
    CircleMoveSystem(component_manager.getSparseList<Position>(),
                     component_manager.getSparseList<AI>());
    RenderSystem(component_manager.getSparseList<Position>(),
                 component_manager.getSparseList<Scale>(),
                 component_manager.getSparseList<Rotation>(),
                 component_manager.getSparseList<Render>());
    elapsed_time += Time::DeltaTime();
    window.update();
  }

  return 0;
}
