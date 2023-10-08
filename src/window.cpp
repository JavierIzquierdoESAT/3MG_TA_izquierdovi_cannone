#include "window.hpp"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "engine.hpp"
#include "input.hpp"

Window::Window(GLFWwindow* w)
    : window_handle_{w}, delta_time_{0.0f}, last_time_{glfwGetTime()} {
  glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_API);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwMakeContextCurrent(w);
  glewInit();
}

Window::Window(Window& w)
    : window_handle_{w.window_handle_},
      delta_time_{0.0f},
      last_time_{glfwGetTime()} {
  w.window_handle_ = NULL;
}

Window::Window(Window&& w) noexcept
    : window_handle_{w.window_handle_},
      delta_time_{0.0f},
      last_time_{glfwGetTime()} {
  w.window_handle_ = NULL;
}

Window::~Window() {
  if (NULL != window_handle_) {
    glfwDestroyWindow(window_handle_);
  }
}

std::optional<Window> Window::Make(const Engine& e, int w, int h,
                                   const char* title) {
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

void Window::swap() const {
  glfwSwapBuffers(window_handle_);
  glClear(GL_COLOR_BUFFER_BIT);
  InputManager::update();
}

void Window::updateDelta() {
  delta_time_ = glfwGetTime() - last_time_;
  last_time_ = glfwGetTime();
}

bool Window::isDone() const { return glfwWindowShouldClose(window_handle_); }

GLFWwindow* Window::initInput() const { return window_handle_; }
