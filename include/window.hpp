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

/// @brief Handles Window
class Window {
  friend class InputManager;

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
  static Window Make(Engine& e, int w, int h, const std::string& title);

  /// @brief checks if the should be closed and refreshes buffer
  /// @return true if the window should close
  bool isDone() const;

  /// @brief swaps screen buffers
  void update() const;

 private:
  Window(GLFWwindow* w, Engine* e);

  /** openGL window handle */
  GLFWwindow* window_handle_;
  Engine* engine_;
};
