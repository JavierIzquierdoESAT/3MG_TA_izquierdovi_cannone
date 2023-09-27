
#include "window.hpp"
#include <GLFW/glfw3.h>


Window::Window(int w, int h, const char* title)
{
  glfwInit();
  window = glfwCreateWindow(w, h, title, NULL, NULL);
}

Window::Window(Window&& w)
{
  this->window = w.window;
  w.window = NULL;
}

std::optional<Window> Window::Make(int w, int h, const char* title)
{
  return Window(w, h, title);
}



Window::~Window()
{
  glfwDestroyWindow(window);
  glfwTerminate();
}

bool Window::isDone() const{
  return glfwWindowShouldClose(window);
}
