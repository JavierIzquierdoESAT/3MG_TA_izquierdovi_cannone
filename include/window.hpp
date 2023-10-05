#pragma once

#include "../src/stdafx.hpp"

struct GLFWwindow;
class Engine;
struct Triangle;

/** Handles Window */
class Window {
 public:
  // copy constructor
  Window(const Window&) = delete;
  // lvalue move constructor
  Window(Window& w);
  // rvalue move constructor
  Window(Window&& w) noexcept;

  ~Window();

  bool getKey(int k) const;

  /** creates the window */
  static std::optional<Window> Make(const Engine& e, int w, int h,
                                    const char* title);

  /** checks if the should be closed and refreshes buffer */
  bool isDone() const;

  void swap() const;

  void initBuffers(Triangle t);

  unsigned int VAO_;
  unsigned int VBO_;

 private:
  Window(GLFWwindow* w);

  /** openGL window handle */
  GLFWwindow* window_handle_;
};
