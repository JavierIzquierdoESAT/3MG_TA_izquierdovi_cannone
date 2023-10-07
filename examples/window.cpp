#include "window.hpp"

#include <array>
#include <iostream>
#include <string>
#include <unordered_map>

#include "Input.hpp"
#include "engine.hpp"
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

    Triangle t;
    t.vertex_[0] = {-1.0f, -1.0f, 0.0f};
    t.vertex_[1] = {1.0f, -1.0f, 0.0f};
    t.vertex_[2] = {0.0f, 1.0f, 0.0f};

    e.initShaders();
    window.initBuffers(t);
    while (!window.isDone()) {
      paint(t, window);
      if (i.ButtonDown("Up")) {
        std::cout << "down" << std::endl;
      }
      if (i.ButtonPressed("Up")) {
        std::cout << "press" << std::endl;
      }
      if (i.ButtonUp("Up")) {
        std::cout << "up" << std::endl;
      }

      window.swap();
    }
  }

  return 0;
}
