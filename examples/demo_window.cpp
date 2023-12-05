#include <array>
#include <iostream>
#include <string>
#include "engine.hpp"
#include "window.hpp"

int main(int, char**) {
  Engine engine;
  Window window = Window::Make(engine, 640, 480, "ventana");
  while (!window.isDone()) {
    window.update();
  }
  return 0;
}
