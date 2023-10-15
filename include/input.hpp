#include <array>
#include <unordered_map>
#include <unordered_set>

struct GLFWwindow;
class Window;

/// @enum allowed input buttons
enum class InputKey {
  UNKNOWN = -1,

  MOUSE_LEFT = 0,
  MOUSE_RIGHT,
  MOUSE_MIDDLE,
  MOUSE_4,
  MOUSE_5,
  MOUSE_6,
  MOUSE_7,
  MOUSE_8,
  
  SCROLL_UP = 8,
  SCROLL_DOWN,

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

/// @brief structure that binds user created actions and physical input
using InputMap = std::unordered_map<std::string, std::vector<InputKey>>;

/// @brief allows for input state retrieval
///
/// this class is closely related to an InputMap  
/// this structure is a map with strings as keys and a vector of InputKey
/// as value,  
/// so you should define your actions as the keys and any number of
/// buttons as value
///
/// ## example
/// ~~~~~~~~~~~~~~~.cpp
/// InputMap inputMap{
///   {"Up", {InputKey::W, InputKey::DOWN}},
///   {"Down", {InputKey::S}},
///   {"Left", {InputKey::A}},
///   {"Right", {InputKey::D}},
/// }
/// ~~~~~~~~~~~~~~~
class InputManager {
 public:
  ~InputManager() = default;

  /// @brief creates a usable inputSystem
  /// @param w Window where the input will be recieved
  /// @param m InputMap includind all actions and mapped keys
  /// @return a usable InputManager
  static InputManager Make(const Window& w, InputMap m);

  /// @brief updates the state of each key
  ///
  /// must be called once per frame for proper functioning of this class
  static void update();

  /// @brief checks if the any of the buttons asigned to an action have been
  /// *pressed* during the frame
  /// @param action to check
  /// @return ture if action has been *performed* false otherwise
  bool ButtonDown(std::string action) const;

  /// @brief checks if the any of the buttons asigned to an action have been
  /// *released* during the frame
  /// @param action to check
  /// @return ture if action has been *performed* false otherwise
  bool ButtonUp(std::string action) const;

  /// @brief checks if the any of the buttons asigned to an action is
  /// *currently held down*
  /// @param action to check
  /// @return ture if action is *currently held down* false otherwise
  bool ButtonPressed(std::string action) const;

 private:
  struct KeyState {
    bool pushed = false;
    bool pressed = false;
    bool released = false;
  };

  InputManager() = delete;
  InputManager(GLFWwindow* w, InputMap m);

  static void GenericButtonCallback(int button, int action);
  static void KeyCallback(GLFWwindow* window, int key, int scancode, int action,
                          int mods);
  static void MouseButtonCallback(GLFWwindow* window, int button, int action,
                                  int mods);
  static void ScrollCallback(GLFWwindow* window, double xoffset,
                             double yoffset);

  inline static std::unordered_map<InputKey, KeyState> s_mapped_keys;
  inline static std::vector<KeyState*> s_modified_keys;

  std::vector<KeyState> findKeyState(const InputMap& map, std::string s) const;

  InputMap map_;
  GLFWwindow* window_;
};
