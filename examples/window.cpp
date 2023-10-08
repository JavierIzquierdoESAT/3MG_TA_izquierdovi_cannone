#include "window.hpp"

#include <array>
#include <iostream>
#include <string>
#include <unordered_map>

#include "Input.hpp"
#include "engine.hpp"
#include "triangle.hpp"
#include "shader_manager.hpp"

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
    ShaderManager s;
    
    s.generateAndCompileShader(kFragmentShader, "../assets/col.fs");
    s.generateAndCompileShader(kVertexShader, "../assets/col.vs");
    s.atachShaders();
    
    Triangle t;

    while (!window.isDone()) {
      if (i.ButtonDown("Up")) {
        std::cout << "down" << std::endl;
      }
      if (i.ButtonPressed("Up")) {
        std::cout << "press" << std::endl;
      }
      if (i.ButtonUp("Up")) {
        std::cout << "up" << std::endl;
      }
      s.useProgram();
      paint(t);
      window.swap();
    }
  }

  return 0;
}
