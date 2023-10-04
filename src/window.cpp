#include "window.hpp"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "engine.hpp"
#include "triangle.hpp"

Window::Window(GLFWwindow* w) : window_handle_{w}, VAO_{0}, VBO_{0} {}

Window::Window(Window& w)
    : window_handle_{w.window_handle_}, VAO_{w.VAO_}, VBO_{w.VBO_} {
  w.window_handle_ = NULL;
}

Window::Window(Window&& w) noexcept
    : window_handle_{w.window_handle_}, VAO_{w.VAO_}, VBO_{w.VBO_} {
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
  glfwPollEvents();
}

void Window::initBuffers(Triangle t) {
  glGenVertexArrays(1, &VAO_);
  glGenBuffers(1, &VBO_);

  glBindVertexArray(VAO_);

  glBindBuffer(GL_ARRAY_BUFFER, VBO_);
  glBufferData(GL_ARRAY_BUFFER, sizeof(t.vertex_), t.vertex_, GL_STATIC_DRAW);

  glVertexAttribPointer(0, t.num_vertex_, GL_FLOAT, GL_FALSE,
                        t.num_vertex_ * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);

  // glBindBuffer(GL_ARRAY_BUFFER, 0);

  // glBindVertexArray(0);
}

bool Window::isDone() const { return glfwWindowShouldClose(window_handle_); }
