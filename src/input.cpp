#include "input.hpp"

#include "GLFW/glfw3.h"
#include "window.hpp"

InputManager::InputManager(const Window& w, InputMap m) : map_{m}, window_{w} {}

InputManager InputManager::Make(const Window& w, InputMap m) {
  return InputManager(w, m);
}

bool InputManager::action(std::string s) {
  auto keys = map_.find(s);
  if (keys != map_.end()) {
    bool res = false;
    for (InputKey key : keys->second) {
      if (window_.getKey((int)key)) {
        res = true;
        break;
      }
    }
    return res;
  }
}
