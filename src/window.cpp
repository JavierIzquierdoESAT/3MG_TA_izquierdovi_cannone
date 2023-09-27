#include "window.hpp"
#include <GLFW/glfw3.h>


Window::Window(int w, int h, const char* title)
{
  glfwInit();
  window = glfwCreateWindow(w, h, title, NULL, NULL);
}

std::optional<Window>& Window::Make(int w, int h, const char* title)
{
  std::optional<Window> win = Window(w, h, title);
  return win;
}



Window::~Window()
{
  glfwDestroyWindow(window);
  glfwTerminate();
}

bool Window::isDone() const{
  return glfwWindowShouldClose(window);
}
