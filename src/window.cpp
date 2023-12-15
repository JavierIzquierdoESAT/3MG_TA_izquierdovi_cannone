#include "window.hpp"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "engine.hpp"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw_gl3.h"
#include "input.hpp"

Window::Window(GLFWwindow* w, Engine* e)
    : window_handle_{w}, engine_{e}, io_{nullptr} {
  glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_API);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwMakeContextCurrent(w);
  glewInit();
  ImGui::CreateContext();
  io_ = &ImGui::GetIO();
  (void)io_;
  ImGui_ImplGlfwGL3_Init(w, true);
  ImGui::StyleColorsDark();
}

Window::Window(Window& w)
    : window_handle_{w.window_handle_}, engine_{w.engine_}, io_{w.io_} {
  w.window_handle_ = NULL;
}

Window::Window(Window&& w) noexcept
    : window_handle_{w.window_handle_}, engine_{w.engine_}, io_{w.io_} {
  w.window_handle_ = NULL;
}

Window::~Window() {
  if (NULL != window_handle_) {
    glfwDestroyWindow(window_handle_);
    ImGui_ImplGlfwGL3_Shutdown();
    ImGui::DestroyContext();
  }
}

Window Window::Make(Engine& e, int w, int h, const std::string& title) {
  GLFWwindow* wind = glfwCreateWindow(w, h, title.c_str(), NULL, NULL);

  const char* description;
  int code = glfwGetError(&description);
  if (description) {
    // TODO: custom error message possible errors
    // GLFW_NOT_INITIALIZED shouldn't happen since we require and engine
    // GLFW_INVALID_ENUM bad monitor value or share value
    // GLFW_INVALID_VALUE bad size or title
    // GLFW_API_UNAVAILABLE GLFW_VERSION_UNAVAILABLE GLFW_PLATFORM_ERROR.
    // user hardware and/or driver errors
    // GLFW_FORMAT_UNAVAILABLE the requested pixel format is not supported.
    std::cout << "Unexpected error: " << code << " - " << description
              << std::endl;
    std::exit(EXIT_FAILURE);
  }

  return Window{wind, &e};
}

void Window::update() const {

  glfwSwapBuffers(window_handle_);
  ImGui::Render();
  //ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());
  glClear(GL_COLOR_BUFFER_BIT);

  InputManager::update();
  engine_->update();
}

bool Window::isDone() const {
  ImGui_ImplGlfwGL3_NewFrame();
  return glfwWindowShouldClose(window_handle_);
}
