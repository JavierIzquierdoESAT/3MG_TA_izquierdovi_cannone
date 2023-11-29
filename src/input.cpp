#include "input.hpp"

#include "GLFW/glfw3.h"
#include "window.hpp"

InputManager::InputManager(const Window& w, InputButtonMap m)
    : map_{m}, window_{w.window_handle_} {
  glfwSetKeyCallback(window_, KeyCallback);
  glfwSetMouseButtonCallback(window_, MouseButtonCallback);
  glfwSetScrollCallback(window_, ScrollCallback);
  glfwSetCursorPosCallback(window_, CursorCallback);
  for (auto& it : m) {
    for (auto& key : it.second) {
      s_mapped_buttons.emplace(
          std::pair<InputButton, KeyState>{key, KeyState()});
    }
  }
}

bool InputManager::buttonDown(std::string s) const {
  bool res = false;
  auto keys = findKeyState(map_, s);
  for (KeyState state : keys) {
    if (state.pushed) {
      res = true;
      break;
    }
  }
  return res;
}
bool InputManager::buttonUp(std::string s) const {
  bool res = false;
  auto keys = findKeyState(map_, s);
  for (KeyState state : keys) {
    if (state.released) {
      res = true;
      break;
    }
  }
  return res;
}
bool InputManager::buttonPressed(std::string s) const {
  bool res = false;
  auto keys = findKeyState(map_, s);
  for (KeyState state : keys) {
    if (state.pressed) {
      res = true;
      break;
    }
  }
  return res;
}

float InputManager::mousePositionX() const { return mouse_x_; }
float InputManager::mousePositionY() const { return mouse_y_; }

std::vector<InputManager::KeyState> InputManager::findKeyState(
    const InputButtonMap& map, std::string s) const {
  auto keys = map.find(s);
  std::vector<KeyState> res;
  res.reserve(10);
  if (keys != map.end()) {
    for (InputButton key : keys->second) {
      auto found = s_mapped_buttons.find(key);
      res.emplace_back(found->second);
    }
  }
  return res;
}

void InputManager::update() {
  for (KeyState* state : s_modified_keys) {
    state->pushed = false;
    state->released = false;
  }
  s_modified_keys.clear();
  glfwPollEvents();
}

void InputManager::ScrollCallback(GLFWwindow*, double, double yoffset) {
  int button = yoffset > 0 ? 8 : 9;
  GenericButtonCallback(button, GLFW_PRESS);
}

void InputManager::MouseButtonCallback(GLFWwindow*, int button, int action,
                                       int) {
  GenericButtonCallback(button, action);
}

void InputManager::KeyCallback(GLFWwindow*, int key, int, int action, int) {
  GenericButtonCallback(key, action);
}

void InputManager::GenericButtonCallback(int button, int action) {
  auto eventKey = s_mapped_buttons.find((InputButton)button);

  if (eventKey != s_mapped_buttons.end()) {
    KeyState& keyState = eventKey->second;

    if (GLFW_PRESS == action) {
      keyState.pushed = true;
      keyState.pressed = true;
    }

    if (GLFW_RELEASE == action) {
      keyState.released = true;
      keyState.pressed = false;
    }

    s_modified_keys.push_back(&keyState);
  }
}
void InputManager::CursorCallback(GLFWwindow*, double xpos, double ypos) {
  mouse_x_ = (float)xpos;
  mouse_y_ = (float)ypos;
}
