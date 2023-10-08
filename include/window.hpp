#pragma once

#include "../src/stdafx.hpp"

struct GLFWwindow;
class Engine;
class Triangle;

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

  /** creates the window */
  static std::optional<Window> Make(const Engine& e, int w, int h,
                                    const char* title);

  /** checks if the should be closed and refreshes buffer */
  bool isDone() const;

  GLFWwindow* initInput() const;

  /** swaps buffers */
  //TODO:: WARNING I'm delteing the const
  void swap() const;


  void updateDelta();
  
  double delta_time_;

 private:
  double last_time_;

  Window(GLFWwindow* w);

  /** openGL window handle */
  GLFWwindow* window_handle_;
};
