#include "window.hpp"
#include "engine.hpp"

int main(int, char**) {


  Engine::Init();
  auto w = Window::Make(640,480,"ventana");

  if (w) {
    auto& window = w.value();
    while (!window.isDone())
    {
      
    }
  }

  Engine::Terminate();
  return 0;
}



