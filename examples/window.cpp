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
    InputManager i = window.addInputManager(inputMap);

    auto shade = ShaderManager::MakeShaders("../assets/col.fs", "../assets/col.vs");
   
    float col[3] = { 1.0f,0.0f,0.0f };
    shade->setUniformValue(DataType::FLOAT_3, col, "initialUniform");

    Triangle t;

    float t_speed = 0.3f;

    while (!window.isDone()) {

      // input
      if (i.buttonPressed("Up")) {
        t.move(Vec3(0, t_speed * Time::delta_time(), 0));
        col[0] = 0.0f;
        col[1] = 0.0f;
        col[2] = 1.0f;
        shade->setUniformValue(DataType::FLOAT_3, col, "initialUniform");
      }
      if (i.buttonPressed("Down")) {
        t.move(Vec3(0, -t_speed * Time::delta_time(), 0));
        col[0] = 0.0f;
        col[1] = 1.0f;
        col[2] = 0.0f;
        shade->setUniformValue(DataType::FLOAT_3, col, "initialUniform");
      }
      if (i.buttonPressed("Left")) {
        t.move(Vec3(-t_speed * Time::delta_time(), 0, 0));
        col[0] = 1.0f;
        col[1] = 0.0f;
        col[2] = 0.0f;
        shade->setUniformValue(DataType::FLOAT_3, col, "initialUniform");
      }
      if (i.buttonPressed("Right")) {
        t.move(Vec3(t_speed * Time::delta_time(), 0, 0));
        col[0] = 1.0f;
        col[1] = 0.0f;
        col[2] = 1.0f;
        shade->setUniformValue(DataType::FLOAT_3, col, "initialUniform");
      }
      std::cout << i.mousePositionX() << "  -  "
                << i.mousePositionY() << std::endl;
      // render
      t.updateBuffers();
      shade->useProgram();
      paint(t);
      window.swap();

      // end frame;
      e.update();
    }
  }

  return 0;
}
