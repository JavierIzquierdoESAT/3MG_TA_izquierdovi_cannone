#include "window.hpp"
#include "engine.hpp"

#include <GLFW/glfw3.h>

#include <iostream>

Window::Window(GLFWwindow* w) : window_handle_{w} {}

Window::Window(Window& w) : window_handle_{w.window_handle_} {
  w.window_handle_ = NULL;
}

Window::Window(Window&& w) noexcept : window_handle_{w.window_handle_} {
  w.window_handle_ = NULL;
}

Window::~Window() {
  if (NULL != window_handle_) {
    glfwDestroyWindow(window_handle_);
  }
}

std::optional<Window> Window::Make(const Engine& e,int w, int h, const char* title) {
  std::optional<Window> res;

  GLFWwindow* wind = glfwCreateWindow(w, h, title, NULL, NULL);

  const char* description;
  int code = glfwGetError(&description);
  if (description) {
    // TODO: custom error message
    std::cout << description << std::endl;
    return res;
  }
  return Window{wind};
}

bool Window::isDone() const {
  glfwPollEvents();
  return glfwWindowShouldClose(window_handle_);
}
