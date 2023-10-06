#include <array>
#include <unordered_map>
#include <unordered_set>

//TODO: find a way to remove this include
#include "GLFW/glfw3.h"

class GLFWwindow;
class Window;

enum class InputKey {
  UNKNOWN = -1,
  SPACE = 32,
  APOSTROPHE = 39,
  COMMA = 44,
  MINUS = 45,
  PERIOD = 46,
  SLASH = 47,
  _0 = 48,
  _1,
  _2,
  _3,
  _4,
  _5,
  _6,
  _7,
  _8,
  _9,
  SEMICOLON = 59,
  EQUAL = 61,
  A = 65,
  B,
  C,
  D,
  E,
  F,
  G,
  H,
  I,
  J,
  K,
  L,
  M,
  N,
  O,
  P,
  Q,
  R,
  S,
  T,
  U,
  V,
  W,
  X,
  Y,
  Z,
  LEFT_BRACKET = 91,
  BACKSLASH = 92,
  RIGHT_BRACKET = 93,
  GRAVE_ACCENT = 96,
  WORLD_1 = 161,
  WORLD_2 = 162,
  ESCAPE = 256,
  ENTER,
  TAB,
  BACKSPACE,
  INSERT,
  DELETE,
  RIGHT,
  LEFT,
  DOWN,
  UP,
  PAGE_UP,
  PAGE_DOWN,
  HOME,
  END,
  CAPS_LOCK = 280,
  SCROLL_LOCK,
  NUM_LOCK,
  PRINT_SCREEN,
  PAUSE,
  F1 = 290,
  F2,
  F3,
  F4,
  F5,
  F6,
  F7,
  F8,
  F9,
  F10,
  F11,
  F12,
  F13,
  F14,
  F15,
  F16,
  F17,
  F18,
  F19,
  F20,
  F21,
  F22,
  F23,
  F24,
  F25,
  KP_0 = 320,
  KP_1,
  KP_2,
  KP_3,
  KP_4,
  KP_5,
  KP_6,
  KP_7,
  KP_8,
  KP_9,
  KP_DECIMAL,
  KP_DIVIDE,
  KP_MULTIPLY,
  KP_SUBTRACT,
  KP_ADD,
  KP_ENTER,
  KP_EQUAL,
  LEFT_SHIFT = 340,
  LEFT_CONTROL,
  LEFT_ALT,
  LEFT_SUPER,
  RIGHT_SHIFT,
  RIGHT_CONTROL,
  RIGHT_ALT,
  RIGHT_SUPER,
  MENU,
  LAST
};

using InputMap = std::unordered_map<std::string, std::vector<InputKey>>;

struct KeyState {
  bool pushed = false;
  bool pressed = false;
  bool released = false;
};

class InputManager {
 public:
  ~InputManager() = default;

  static InputManager Make(const Window& w, InputMap m);
  static void key_callback(GLFWwindow* window, int key, int scancode,
                           int action, int mods);
  inline static std::unordered_map<InputKey, KeyState> s_mapped_keys;

  /** checks if any of the keys asigned to de action is pressed*/
  bool ButtonDown(std::string) const;
  bool ButtonUp(std::string) const;
  bool ButtonPressed(std::string) const;

 private:
  InputManager() = delete;
  InputManager(GLFWwindow* w, InputMap m);

  std::vector<KeyState> findKeyState(const InputMap& map, std::string s) const;

  InputMap map_;
  GLFWwindow* window_;
};
