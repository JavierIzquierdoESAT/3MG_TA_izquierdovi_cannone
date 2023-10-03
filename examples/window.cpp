#include "window.hpp"
#include "engine.hpp"

int main(int, char**) {

  Engine e;

  auto w = Window::Make(e,640,480,"ventana");

  if (w) {
    auto& window = w.value();
    while (!window.isDone())
    {
      
    }
  }

  return 0;
}



