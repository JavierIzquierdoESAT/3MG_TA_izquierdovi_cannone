#include "window.hpp"

#include <array>
#include <string>
#include <unordered_map>
#include <iostream>

#include "GL/glew.h"
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
      if (i.action("Up")) {
        std::cout << "paint" << std::endl;
        paint(t, window);
      }

      window.swap();
    }
  }

  return 0;
}
