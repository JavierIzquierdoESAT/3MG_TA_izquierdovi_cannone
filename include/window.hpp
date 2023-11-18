#pragma once
#include <string>
#include <unordered_map>
#include <vector>

#include "../src/stdafx.hpp"

struct GLFWwindow;
class Engine;
class Triangle;

enum class InputButton;
using InputButtonMap =
    std::unordered_map<std::string, std::vector<InputButton>>;
class InputManager;

/** Handles Window */
class Window {
 public:
  /// @brief non copyable object
  Window(const Window&) = delete;
  /// @brief lvalue move constructor
  /// @param w Window to move
  Window(Window& w);
  /// @brief rvalue move constructor
  /// @param w Window to move
  Window(Window&& w) noexcept;

  ~Window();

  /// @brief creates a window
  /// @param e Engine is needed for internal stuff
  /// @param w Window width in pixels
  /// @param h Window height in pixels
  /// @param title Name of the window
  /// @return a Window object if the creation was succesful
  ///
  /// since this function returns an optional you should check if the window was
  /// returned correctly before using it
  /// ~~~~~~~~.cpp
  /// auto w = Window::Make(e, 640, 480, "ventana");
  /// if (w) {
  ///  auto& window = w.value();
  /// ~~~~~~~~
  static Window Make(const Engine& e, int w, int h, const std::string& title);

  /// @brief checks if the should be closed and refreshes buffer
  /// @return true if the window should close
  ///
  /// this should be used as the main loop exit condition
  /// ~~~~~~~~.cpp
  /// while (!window.isDone()) {}
  /// ~~~~~~~~
  bool isDone() const;

  /// @brief creates and returns an InputManager that will capture input for
  /// this window
  /// @return The InputManager object created
  InputManager addInputManager(InputButtonMap imput_map) const;

  /// @brief swaps screen buffers
  ///
  /// it should be called at the end of every frame in order to show what was
  /// rendered on screen
  void swap() const;

 private:
  Window(GLFWwindow* w);

  /** openGL window handle */
  GLFWwindow* window_handle_;
};
