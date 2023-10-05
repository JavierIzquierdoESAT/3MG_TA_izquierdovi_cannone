
#include <array>
#include <unordered_map>

#include "GLFW/glfw3.h"

enum class InputKey {
  W = GLFW_KEY_W,
  S = GLFW_KEY_S,
  A = GLFW_KEY_A,
  D = GLFW_KEY_D
};

using InputMap = std::unordered_map<std::string, std::vector<InputKey>>;

class Window;

class InputManager {
 public:
  ~InputManager() = default;

  static InputManager Make(const Window& w, InputMap m);

  /** checks if any of the keys asigned to de action has been pressed during the
   * last update */
  bool action(std::string);

 private:
  InputManager();
  InputManager(const Window& w, InputMap m);

  InputMap map_;
  const Window& window_;
};
