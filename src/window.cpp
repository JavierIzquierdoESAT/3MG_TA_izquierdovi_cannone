#include "window.hpp"

#include <GLFW/glfw3.h>

Window::Window(int w, int h, const char* title)
    : window_handle_{nullptr} {
  glfwInit();
  window_handle_ = glfwCreateWindow(w, h, title, NULL, NULL);
}

Window::Window(Window& w) : window_handle_{w.window_handle_} {
  w.window_handle_ = NULL;
}

Window::Window(Window&& w) noexcept 
    : window_handle_{w.window_handle_} {
  w.window_handle_ = NULL;
}

Window::~Window() {
  if (NULL != window_handle_) {
    glfwDestroyWindow(window_handle_);
    glfwTerminate();
  }
}

std::optional<Window> Window::Make(int w, int h, const char* title) {
  return Window{ w, h, title };
}

bool Window::isDone() const {
  glfwPollEvents();
  return glfwWindowShouldClose(window_handle_);
}
