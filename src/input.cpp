#include "input.hpp"

#include "GLFW/glfw3.h"
#include "window.hpp"

InputManager::InputManager(GLFWwindow* w, InputMap m) : map_{m}, window_{w} {
  glfwSetKeyCallback(window_, key_callback);
  for (auto it : m) {
    for (auto key : it.second) {
      s_mapped_keys.emplace(std::pair<InputKey, KeyState>{key, KeyState()});
    }
  }
}

InputManager InputManager::Make(const Window& w, InputMap m) {
  auto handle = w.initInput();
  return InputManager(handle, m);
}

bool InputManager::ButtonDown(std::string s) const {
  bool res = false;
  auto keys = findKeyState(map_, s);
  for (KeyState state : keys) {
    if (state.pushed) res = true;
    break;
  }
  return res;
}
bool InputManager::ButtonUp(std::string s) const {
  bool res = false;
  auto keys = findKeyState(map_, s);
  for (KeyState state : keys) {
    if (state.released) res = true;
    break;
  }
  return res;
}
bool InputManager::ButtonPressed(std::string s) const {
  bool res = false;
  auto keys = findKeyState(map_, s);
  for (KeyState state : keys) {
    if (state.pressed) res = true;
    break;
  }
  return res;
}

std::vector<KeyState> InputManager::findKeyState(const InputMap& map,
                                                 std::string s) const {
  auto keys = map.find(s);
  std::vector<KeyState> res;
  res.reserve(10);
  if (keys != map.end()) {
    for (InputKey key : keys->second) {
      auto found = s_mapped_keys.find(key);
      res.emplace_back(found->second);
    }
    return res;
  }
}

void InputManager::update() { 
  for (KeyState* state : s_modified_keys) {
    state->pushed = false;
    state->released = false;
  }
  s_modified_keys.clear();
  glfwPollEvents(); 
}

//TODO: update to clear pushhed and released afte a frame
void InputManager::key_callback(GLFWwindow* window, int key, int scancode,
                                int action, int mods) {
  auto eventKey = s_mapped_keys.find((InputKey)key);

  if (eventKey != s_mapped_keys.end()) {
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
