#include "window.hpp"

#include <array>
#include <iostream>
#include <string>
#include <unordered_map>

#include "Input.hpp"
#include "engine.hpp"
#include "shader_manager.hpp"
#include "time.hpp"
#include "triangle.hpp"

InputMap inputMap{
    {"Up", {InputKey::W}},
    {"Down", {InputKey::S}},
    {"Left", {InputKey::A}},
    {"Right", {InputKey::D}},
};

int main(int, char**) {
  Engine e;

  auto w = Window::Make(e, 640, 480, "ventana");
  if (w) {
    auto& window = w.value();

    InputManager i = InputManager::Make(window, inputMap);

    // Ideal input form user:
    // ShaderProgram sp = ShaderProgram::Make("../assets/col.fs",
    //                                        "../assets/col.vs")
    ShaderManager s;
    s.generateAndCompileShader(kFragmentShader, "../assets/col.fs");
    s.generateAndCompileShader(kVertexShader, "../assets/col.vs");
    s.attachShaders();

    Triangle t;

    float t_speed = 0.3f;

    while (!window.isDone()) {
      // input
      if (i.ButtonPressed("Up")) {
        t.move(Vec3(0, t_speed * Time::delta_time(), 0));
      }
      if (i.ButtonPressed("Down")) {
        t.move(Vec3(0, -t_speed * Time::delta_time(), 0));
      }
      if (i.ButtonPressed("Left")) {
        t.move(Vec3(-t_speed * Time::delta_time(), 0, 0));
      }
      if (i.ButtonPressed("Right")) {
        t.move(Vec3(t_speed * Time::delta_time(), 0, 0));
      }

      // render
      t.updateBuffers();
      s.useProgram();
      paint(t);
      window.swap();

      // end frame;
      e.update();
    }
  }

  return 0;
}
