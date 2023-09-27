#include "window.hpp"

int main(int, char**) {

  auto w = Window::Make(640,480,"ventana");


  if (w) {
    auto& window = w.value();
    while (!window.isDone())
    {
      
    }
  }

  return 0;
}



